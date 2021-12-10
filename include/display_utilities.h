#include "esphome.h"

void drawHeader(esphome::display::DisplayBuffer& it, esphome::Color color);
void showCalibration(esphome::display::DisplayBuffer& it, esphome::display::Font* font, esphome::Color color_info, esphome::Color color_nok, esphome::switch_::Switch* co2_calibrate, esphome::binary_sensor::BinarySensor* co2_calibrated);
void showStatus(esphome::display::DisplayBuffer& it, esphome::display::Font* font, esphome::Color color_ok, esphome::Color color_nok, esphome::binary_sensor::BinarySensor* system_status);
