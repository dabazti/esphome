#include "dtsd_1352.h"
#include "dtsd_1352_registers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace dtsd_1352 {

static const char *const TAG = "dtsd_1352";

static const uint8_t MODBUS_CMD_READ_IN_REGISTERS = 0x03;
static const uint8_t MODBUS_REGISTER_COUNT = 80;  // 80 x 16-bit registers

void dtsd1352::on_modbus_data(const std::vector<uint8_t> &data) {
  if (data.size() < MODBUS_REGISTER_COUNT * 2) {
    ESP_LOGW(TAG, "Invalid size for DTSD1352!");
    return;
  }

  auto dtsd_1352_get_float = [&](size_t i, float unit) -> float {
    uint32_t temp = encode_uint32(data[i], data[i + 1], data[i + 2], data[i + 3]);

    float f;
    memcpy(&f, &temp, sizeof(f));
    return (f * unit);
  };

  float total_active_energy = dtsd_1352_get_float(DTSD_TOTAL_ACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float import_active_energy = dtsd_1352_get_float(DTSD_IMPORT_ACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float export_active_energy = dtsd_1352_get_float(DTSD_EXPORT_ACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float total_reactive_energy = dtsd_1352_get_float(DTSD_TOTAL_REACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float import_reactive_energy = dtsd_1352_get_float(DTSD_IMPORT_REACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float export_reactive_energy = dtsd_1352_get_float(DTSD_EXPORT_REACTIVE_ENERGY * 2, NO_DEC_UNIT);
  float active_power = dtsd_1352_get_float(DTSD_ACTIVE_POWER * 2, MULTIPLY_THOUSAND_UNIT);
  float reactive_power = dtsd_1352_get_float(DTSD_REACTIVE_POWER * 2, MULTIPLY_THOUSAND_UNIT);
  float apparent_power = dtsd_1352_get_float(DTSD_APPARENT_POWER * 2, MULTIPLY_THOUSAND_UNIT);
  float voltage = dtsd_1352_get_float(DTSD_VOLTAGE * 2, NO_DEC_UNIT);
  float current = dtsd_1352_get_float(DTSD_CURRENT * 2, NO_DEC_UNIT);
  float power_factor = dtsd_1352_get_float(DTSD_POWER_FACTOR * 2, NO_DEC_UNIT);
  float frequency = dtsd_1352_get_float(DTSD_FREQUENCY * 2, NO_DEC_UNIT);

  if (this->total_active_energy_sensor_ != nullptr)
    this->total_active_energy_sensor_->publish_state(total_active_energy);
  if (this->import_active_energy_sensor_ != nullptr)
    this->import_active_energy_sensor_->publish_state(import_active_energy);
  if (this->export_active_energy_sensor_ != nullptr)
    this->export_active_energy_sensor_->publish_state(export_active_energy);
  if (this->total_reactive_energy_sensor_ != nullptr)
    this->total_reactive_energy_sensor_->publish_state(total_reactive_energy);
  if (this->import_reactive_energy_sensor_ != nullptr)
    this->import_reactive_energy_sensor_->publish_state(import_reactive_energy);
  if (this->export_reactive_energy_sensor_ != nullptr)
    this->export_reactive_energy_sensor_->publish_state(export_reactive_energy);
  if (this->active_power_sensor_ != nullptr)
    this->active_power_sensor_->publish_state(active_power);
  if (this->reactive_power_sensor_ != nullptr)
    this->reactive_power_sensor_->publish_state(reactive_power);
  if (this->apparent_power_sensor_ != nullptr)
    this->apparent_power_sensor_->publish_state(apparent_power);
  if (this->voltage_sensor_ != nullptr)
    this->voltage_sensor_->publish_state(voltage);
  if (this->current_sensor_ != nullptr)
    this->current_sensor_->publish_state(current);
  if (this->power_factor_sensor_ != nullptr)
    this->power_factor_sensor_->publish_state(power_factor);
  if (this->frequency_sensor_ != nullptr)
    this->frequency_sensor_->publish_state(frequency);
}

void dtsd1352::update() { this->send(MODBUS_CMD_READ_IN_REGISTERS, 0, MODBUS_REGISTER_COUNT); }
void dtsd1352::dump_config() {
  ESP_LOGCONFIG(TAG, "DTSD1352:");
  ESP_LOGCONFIG(TAG, "  Address: 0x%02X", this->address_);
  LOG_SENSOR("  ", "Total Active Energy", this->total_active_energy_sensor_);
  LOG_SENSOR("  ", "Import Active Energy", this->import_active_energy_sensor_);
  LOG_SENSOR("  ", "Export Active Energy", this->export_active_energy_sensor_);
  LOG_SENSOR("  ", "Total Reactive Energy", this->total_reactive_energy_sensor_);
  LOG_SENSOR("  ", "Import Reactive Energy", this->import_reactive_energy_sensor_);
  LOG_SENSOR("  ", "Export Reactive Energy", this->export_reactive_energy_sensor_);
  LOG_SENSOR("  ", "Active Power", this->active_power_sensor_);
  LOG_SENSOR("  ", "Reactive Power", this->reactive_power_sensor_);
  LOG_SENSOR("  ", "Apparent Power", this->apparent_power_sensor_);
  LOG_SENSOR("  ", "Voltage", this->voltage_sensor_);
  LOG_SENSOR("  ", "Current", this->current_sensor_);
  LOG_SENSOR("  ", "Power Factor", this->power_factor_sensor_);
  LOG_SENSOR("  ", "Frequency", this->frequency_sensor_);
}

}  // namespace dtsd_1352
}  // namespace esphome
