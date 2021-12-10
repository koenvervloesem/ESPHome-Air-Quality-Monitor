#include "esphome.h"

void drawHeader(esphome::display::DisplayBuffer& it, esphome::display::Font* font, esphome::Color color_header, esphome::Color color_ok, esphome::Color color_nok, esphome::Color color_info, esphome::switch_::Switch* co2_calibrate, esphome::binary_sensor::BinarySensor* co2_calibrated, esphome::binary_sensor::BinarySensor* system_status);
