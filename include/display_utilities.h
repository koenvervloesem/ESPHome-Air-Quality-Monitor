#include "esphome.h"

// Draw header and frame
void drawHeader(esphome::display::DisplayBuffer& it, esphome::Color color) {
    it.rectangle(0,  0, it.get_width(), it.get_height(), color);
    it.rectangle(0, 20, it.get_width(), it.get_height(), color);
}

// Show calibration state at the left
void showCalibration(esphome::display::DisplayBuffer& it, esphome::display::Font* font, esphome::Color color_info, esphome::Color color_nok, esphome::switch_::Switch* co2_calibrate, esphome::binary_sensor::BinarySensor* co2_calibrated) {
    if ((*co2_calibrate).state) {
        it.print(5, 5, font, color_info, esphome::display::TextAlign::TOP_LEFT, "Calibrating...");
    }
    else if (!(*co2_calibrated).state) {
        it.print(5, 5, font, color_nok, esphome::display::TextAlign::TOP_LEFT, "Calibrate");
    }
}

// Show connection state at the right
void showStatus(esphome::display::DisplayBuffer& it, esphome::display::Font* font, esphome::Color color_ok, esphome::Color color_nok, esphome::binary_sensor::BinarySensor* system_status) {
    if ((*system_status).state) {
        it.print(it.get_width() - 5, 5, font, color_ok, esphome::display::TextAlign::TOP_RIGHT, "Online");
    }
    else {
        it.print(it.get_width() - 5, 5, font, color_nok, esphome::display::TextAlign::TOP_RIGHT, "Offline");
    }
}
