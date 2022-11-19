###########################
ESPHome Air Quality Monitor
###########################

.. image:: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/workflows/Build/badge.svg
   :target: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/actions
   :alt: Continuous integration

.. image:: https://img.shields.io/github/license/koenvervloesem/ESPHome-Air-Quality-Monitor.svg
   :target: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/LICENSE
   :alt: License

This `ESPHome <https://esphome.io/>`_ configuration builds firmware for a DIY indoor air quality monitor. It monitors:

- CO₂ concentration
- PM2.5 and PM10 concentration
- temperature, humidity and pressure

It optionally shows feedback for the current air quality with an RGB LED: green if the air quality is good, yellow if it's acceptable, and red if it's bad. An alternative is showing the sensor measurements on a display.

You can build an example implementation on a perfboard in a project box like this:

.. image:: static/air-quality-monitor-on-perfboard.jpg
   :alt: A DIY air quality monitor on a perfboard in a project box

Or a portable version with battery (at the back) and display:

.. image:: static/air-quality-monitor-with-display.jpg
   :alt: A DIY air quality monitor with display and battery

Note the DC/DC boost converter next to the ESP32 board. It always supplies 5 V to the T6615 and SDS011, irrespective of the input voltage (3.7 V if running on the battery and 5 V if running from the USB-C power).

************
Requirements
************

- ESP8266 or ESP32 board
- `Winsen MH-Z19B <https://www.winsen-sensor.com/sensors/co2-sensor/mh-z19b.html>`_ or `Telaire T6615 <https://www.amphenol-sensors.com/en/telaire/co2/525-co2-sensor-modules/319-t6615>`_ CO₂ sensor
- `Nova Fitness SDS011 <http://inovafitness.com/en/a/chanpinzhongxin/95.html>`_ particulate matter (PM) sensor
- `Bosch BME280 <https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/>`_ breakout board (the 3.3 V version)
- ESPHome

Optionally:

- Common cathode RGB LED (or separate red, green and blue LEDs)
- 220 Ω resistor and two 47 Ω resistors
- LiPo or Li-Ion battery
- DC/DC boost converter with 5 V output

***********
Connections
***********

I have tested this code with:

- the NodeMCU v2 ESP8266
- the ESP32-DevKitC V4
- the LilyGO TTGO T-Display ESP32 (using the built-in display instead of an RGB LED for feedback)

Here are the connections to the pins of these boards:

+--------------------+-----------------+------------------+----------------------+
| Component          | NodeMCU ESP8266 | ESP32-DevKitC V4 | TTGO T-Display ESP32 |
+====================+=================+==================+======================+
| BME280 SCL         | D1              | GPIO21           | GPIO21               |
+--------------------+-----------------+------------------+----------------------+
| BME280 SDA         | D2              | GPIO22           | GPIO22               |
+--------------------+-----------------++-----------------+----------------------+
| MH-Z19B / T6615 TX | D4              | GPIO35           | GPIO39               |
+--------------------+-----------------+------------------+----------------------+
| MH-Z19B / T6615 RX | D5              | GPIO32           | GPIO32               |
+--------------------+-----------------+------------------+----------------------+
| SDS011 TX          | D3              | GPIO34           | GPIO25               |
+--------------------+-----------------+------------------+----------------------+
| SDS011 RX          | D6              | GPIO33           | GPIO33               |
+--------------------+-----------------+------------------+----------------------+
| LED red            | D7              | GPIO5            | /                    |
+--------------------+-----------------+------------------+----------------------+
| LED green          | D8              | GPIO17           | /                    |
+--------------------+-----------------+------------------+----------------------+
| LED blue           | TX              | GPIO16           | /                    |
+--------------------+-----------------+------------------+----------------------+

Make sure to connect the power and ground connections too. The BME280 needs 3.3 V, the MH-Z19B, T6615 and SDS011 need 5 V.

The red component of the RGB LED needs a current-limiting resistor of 220 Ω, while the other two color components need a 47 Ω resistor.

**********
Modularity
**********

This is a modular ESPHome configuration split up in various YAML files that you can import as `packages <https://esphome.io/guides/configuration-types.html#packages>`_. You can find these in the directory `common <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/tree/main/common>`_:

`aqi.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/aqi.yaml>`_
  Computes the air quality index (AQI) value (good, acceptable, bad) based on the current CO₂ concentration and the 24-hour averages of the PM2.5 and PM10 concentrations. This value is published as a text sensor and shown as a color (green, yellow, red) on the RGB LED.
`base.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/base.yaml>`_
  Sets up the basic ESPHome functionality for the board, including Wi-Fi, a captive portal, logger, Home Assistant API and OTA support. It also sets the threshold values for the CO₂, PM2.5 and PM10 concentrations, as well as the messages when the air quality is good, acceptable or bad.
`bme280.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/bme280.yaml>`_
  Sets up the BME280 sensor for temperature, humidity and pressure and the I²C bus it uses.
`display.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/display.yaml>`_
  Configures colors and fonts as well as graphs for the CO₂ and particulate matter concentrations.
`mh-z19b.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/mh-z19b.yaml>`_
  Sets up the MH-Z19B CO₂ sensor, a binary sensor that shows whether the sensor has been calibrated yet (and sets the LED to blue when it isn't) and a switch to calibrate the sensor.
`no_feedback/aqi.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/no_feedback/aqi.yaml>`_
  Use this if you don't want to show AQI status.
`no_feedback/calibration.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/no_feedback/calibration.yaml>`_
  Use this if you don't want to show calibration status.
`rgb_led/aqi.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/rgb_led/aqi.yaml>`_
  Shows AQI status on the RGB LED.
`rgb_led/calibration.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/rgb_led/calibration.yaml>`_
  Shows calibration status on the RGB LED.
`rgb_led/esp32.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/rgb_led/esp32.yaml>`_
  Sets up the RGB LED on the ESP32 with its LEDC peripheral (a hardware PWM).
`rgb_led/esp8266.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/rgb_led/esp8266.yaml>`_
  Sets up the RGB LED on the ESP8266 with software PWM.
`sds011.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/sds011.yaml>`_
  Sets up the SDS011 PM sensor.
`t6615.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/common/t6615.yaml>`_
  Sets up the T6615 CO₂ sensor, which doesn't need calibration.

*****
Usage
*****

To use this configuration, create a YAML file with:

- substitutions for all pin numbers used by the components, your device's name, platform and board and parameters like update intervals.
- packages that include the relevant YAML files in the ``common`` directory.

There are three example configurations in this repository:

- `esphome-air-quality-monitor-esp8266.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/esphome-air-quality-monitor-esp8266.yaml>`_ for the NodeMCU v2 ESP8266
- `esphome-air-quality-monitor-esp32.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/esphome-air-quality-monitor-esp32.yaml>`_ for the ESP32-DevKitC V4
- `esphome-air-quality-monitor-t-display.yaml <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/main/esphome-air-quality-monitor-t-display.yaml>`_ for the TTGO T-Display ESP32

After this, flash the firmware to your device, e.g. with:

.. code-block:: console

  esphome run esphome-air-quality-monitor-esp32.yaml

After you have added your device to Home Assistant's ESPHome integration, the air quality measurements are available in Home Assistant and you can start the calibration of the CO₂ sensor from within Home Assistant too (or with the top button on the TTGO T-Display ESP32).

If you successfully created a configuration for another ESP8266 or ESP32 board, please contribute this configuration with a `pull request <https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/pulls>`_.

**********************
Web-based installation
**********************

If you have built one of the above three example configurations with exactly the same pinout and the same ESP32/ESP8266 modules, you can install the latest version of the firmware on your air quality monitor from our `installation page <https://koenvervloesem.github.io/ESPHome-Air-Quality-Monitor/>`_ via USB, as well as setting up Wi-Fi and adding the device to Home Assistant. This requires a web browser that supports `Web Serial <https://caniuse.com/web-serial>`_ (which is a recent Chrome, Edge or Opera).

**************
Customizations
**************

Thanks to the modularity of the code, it shouldn't be that difficult to create a variant of this project with other sensors. Here are some suggestions:

Change the temperature, humidity and pressure sensor
  This sensor is currently not referenced in the other YAML files, so you can just add a configuration file for another sensor, disable the package for the BME280 and add a package for the other sensor.
Change the CO₂ sensor
  Make sure you give the CO₂ value of your sensor the ID ``co2_value`` and create a binary sensor for its calibration state with ID ``co2_calibrated``.
Change the RGB LED
  You can swap the classical RGB LED for another light, as long as it has the ID ``led_rgb`` and it's a light with platform ``rgb`` (with red, green and blue components).
Change the PM sensor
  Make sure you give the PM2.5 and PM10 values of your sensor the IDs ``pm2_5_value`` and ``pm10_value``.

With these changes, the rest of the code should still work.

If you successfully created a customization, please contribute this with a `pull request`_, ideally with an example configuration.

More complex customizations could be supported in future versions of this project.

************************
Learn more about ESPHome
************************

If you want to learn more about ESPHome, read my book `Getting Started with ESPHome: Develop your own custom home automation devices <https://koen.vervloesem.eu/books/getting-started-with-esphome/>`_ and the accompanying GitHub repository `koenvervloesem/Getting-Started-with-ESPHome <https://github.com/koenvervloesem/Getting-Started-with-ESPHome/>`_.

*******
License
*******

This project is provided by `Koen Vervloesem <http://koen.vervloesem.eu>`_ as open source software with the MIT license. See the `LICENSE file <LICENSE>`_ for more information.

The included Roboto font is licensed under the `Apache License, Version 2.0 <https://fonts.google.com/specimen/Roboto#license>`_.

The C++/runtime codebase of the ESPHome project (file extensions .c, .cpp, .h, .hpp, .tcc, .ino) are published under the GPLv3 license. The Python codebase and all other parts of the ESPHome codebase are published under the MIT license. See the `ESPHome License <https://github.com/esphome/esphome/blob/dev/LICENSE>`_ for more information.
