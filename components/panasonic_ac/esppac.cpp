#include "esppac.h"

#include "esphome/core/log.h"

#include "esppac.h"

namespace esphome {
namespace panasonic_ac {

void PanasonicAC::set_outside_temperature_sensor(sensor::Sensor *outside_temperature_sensor) {
  this->outside_temperature_sensor_ = outside_temperature_sensor;
}

void PanasonicAC::set_vertical_swing_select(select::Select *vertical_swing_select) {
  this->vertical_swing_select_ = vertical_swing_select;
  if (this->vertical_swing_select_ != nullptr) {
    this->vertical_swing_select_->add_on_state_callback([this](const std::string &value, size_t index) {
      if (value == this->vertical_swing_state_)
        return;
      this->on_vertical_swing_change(value);
    });
  }
}

void PanasonicAC::set_horizontal_swing_select(select::Select *horizontal_swing_select) {
  this->horizontal_swing_select_ = horizontal_swing_select;
  if (this->horizontal_swing_select_ != nullptr) {
    this->horizontal_swing_select_->add_on_state_callback([this](const std::string &value, size_t index) {
      if (value == this->horizontal_swing_state_)
        return;
      this->on_horizontal_swing_change(value);
    });
  }
}

void PanasonicAC::set_nanoex_switch(switch_::Switch *nanoex_switch) {
  this->nanoex_switch_ = nanoex_switch;
}

void PanasonicAC::set_eco_switch(switch_::Switch *eco_switch) {
  this->eco_switch_ = eco_switch;
}

void PanasonicAC::set_econavi_switch(switch_::Switch *econavi_switch) {
  this->econavi_switch_ = econavi_switch;
}

void PanasonicAC::set_mild_dry_switch(switch_::Switch *mild_dry_switch) {
  this->mild_dry_switch_ = mild_dry_switch;
}

void PanasonicAC::set_current_power_consumption_sensor(sensor::Sensor *current_power_consumption_sensor) {
  this->current_power_consumption_sensor_ = current_power_consumption_sensor;
}

void PanasonicAC::set_current_temperature_sensor(sensor::Sensor *current_temperature_sensor) {
  this->current_temperature_sensor_ = current_temperature_sensor;
}

void PanasonicAC::setup() {
  // Initialization code here
  this->init_time_ = millis();
  this->last_read_ = 0;
  this->last_packet_sent_ = 0;
  this->last_packet_received_ = 0;
}

void PanasonicAC::loop() {
  // Loop logic here, e.g. read UART data, handle state, etc.
  this->read_data();
}

climate::ClimateTraits PanasonicAC::traits() {
  auto traits = climate::ClimateTraits();
  traits.set_supports_current_temperature(true);
  traits.set_supports_two_point_fan_mode(true);
  traits.set_supports_swing_mode(true);
  traits.set_supports_action(true);
  traits.set_supports_away(true);
  traits.set_supports_eco(true);
  traits.set_supports_heat_cool_mode(true);
  traits.set_supports_on_off(true);
  return traits;
}

void PanasonicAC::read_data() {
  // Implementation to read UART data into rx_buffer_ and parse packets
}

void PanasonicAC::update_outside_temperature(int8_t temperature) {
  if (this->outside_temperature_sensor_ != nullptr)
    this->outside_temperature_sensor_->publish_state(temperature);
}

void PanasonicAC::update_current_temperature(int8_t temperature) {
  if (this->current_temperature_sensor_ != nullptr)
    this->current_temperature_sensor_->publish_state(temperature);
}

void PanasonicAC::update_target_temperature(uint8_t raw_value) {
  // Convert raw_value to temperature and update climate target
}

void PanasonicAC::update_swing_horizontal(const std::string &swing) {
  this->horizontal_swing_state_ = swing;
}

void PanasonicAC::update_swing_vertical(const std::string &swing) {
  this->vertical_swing_state_ = swing;
}

void PanasonicAC::update_nanoex(bool nanoex) {
  this->nanoex_state_ = nanoex;
}

void PanasonicAC::update_eco(bool eco) {
  this->eco_state_ = eco;
}

void PanasonicAC::update_econavi(bool econavi) {
  this->econavi_state_ = econavi;
}

void PanasonicAC::update_mild_dry(bool mild_dry) {
  this->mild_dry_state_ = mild_dry;
}

void PanasonicAC::update_current_power_consumption(int16_t power) {
  if (this->current_power_consumption_sensor_ != nullptr)
    this->current_power_consumption_sensor_->publish_state(power);
}

climate::ClimateAction PanasonicAC::determine_action() {
  // Determine current climate action (heat, cool, idle, etc.)
  return climate::ClimateAction::CLIMATE_ACTION_OFF;
}

void PanasonicAC::log_packet(std::vector<uint8_t> data, bool outgoing) {
  // Log packet data for debug purposes
}

}  // namespace panasonic_ac
}  // namespace esphome
