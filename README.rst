###########################
ESPHome Air Quality Monitor
###########################

.. image:: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/workflows/Build/badge.svg
   :target: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/actions
   :alt: Continuous integration

.. image:: https://img.shields.io/github/license/koenvervloesem/ESPHome-Air-Quality-Monitor.svg
   :target: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/blob/master/LICENSE
   :alt: License

This `ESPHome <https://esphome.io/>`_ configuration builds firmware for a DIY indoor air quality monitor. It monitors:

- CO₂ concentration
- PM2.5 and PM10 concentration
- temperature, humidity and pressure

It shows feedback for the current air quality with an RGB LED: green if the air quality is good, yellow if it's acceptable, and red if it's bad.

You can build this on a perfboard in a project box like this:

.. image:: https://github.com/koenvervloesem/ESPHome-Air-Quality-Monitor/raw/main/air-quality-monitor-on-perfboard.jpg
   :alt: A DIY air quality monitor on a perfboard in a project box

************
Requirements
************

- ESP8266 or ESP32 board
- `Winsen MH-Z19B <https://www.winsen-sensor.com/sensors/co2-sensor/mh-z19b.html>`_ CO₂ sensor
- `Nova Fitness SDS011 <http://inovafitness.com/en/a/chanpinzhongxin/95.html>`_ particulate matter (PM) sensor
- `Bosch BME280 <https://www.bosch-sensortec.com/products/environmental-sensors/humidity-sensors-bme280/>`_ breakout board (the 3.3 V version)
- RGB LED
- 220 Ω resistor and two 47 Ω resistors
- ESPHome

***********
Connections
***********

I have tested this code with:

- the NodeMCU v2 ESP8266
- the ESP32-DevKitC V4

Here are the connections to the pins of these boards:

+--------------+-----------------+------------------+
| Component    | NodeMCU ESP8266 | ESP32-DevKitC V4 |
+==============+=================+==================+
| BME280 SCL   | D1              | GPIO21           |
+--------------+-----------------+------------------+
| BME280 SDA   | D2              | GPIO22           |
+--------------+-----------------++-----------------+
| MH-Z19B TX   | D4              | GPIO35           |
+--------------+-----------------+------------------+
| MH-Z19B RX   | D5              | GPIO32           |
+--------------+-----------------+------------------+
| SDS011 TX    | D3              | GPIO34           |
+--------------+-----------------+------------------+
| SDS011 RX    | D6              | GPIO33           |
+--------------+-----------------+------------------+
| LED red      | D7              | GPIO5            |
+--------------+-----------------+------------------+
| LED green    | D8              | GPIO17           |
+--------------+-----------------+------------------+
| LED blue     | TX              | GPIO16           |
+--------------+-----------------+------------------+

Make sure to connect the power and ground connections too. The BME280 needs 3.3 V, the MH-Z19B and SDS011 need 5 V.

The red component of the RGB LED needs a current-limiting resistor of 220 Ω, while the other two color components need a 47 Ω resistor.

*****
Usage
*****

TODO

*******
License
*******

This project is provided by `Koen Vervloesem <http://koen.vervloesem.eu>`_ as open source software with the MIT license. See the `LICENSE file <LICENSE>`_ for more information.

The C++/runtime codebase of the ESPHome project (file extensions .c, .cpp, .h, .hpp, .tcc, .ino) are published under the GPLv3 license. The Python codebase and all other parts of the ESPHome codebase are published under the MIT license. See the `ESPHome License <https://github.com/esphome/esphome/blob/dev/LICENSE>`_ for more information.
