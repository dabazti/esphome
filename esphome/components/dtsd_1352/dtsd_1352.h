#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/components/modbus/modbus.h"

#include <vector>

namespace esphome {
namespace dtsd_1352 {

#define DTSD_1352_SENSOR(name) \
 protected: \
  sensor::Sensor *name##_sensor_{nullptr}; \
\
 public: \
  void set_##name##_sensor(sensor::Sensor *(name)) { this->name##_sensor_ = name; }

class dtsd1352 : public PollingComponent, public modbus::ModbusDevice {
 public:
  DTSD_1352_SENSOR(total_active_energy)
  DTSD_1352_SENSOR(import_active_energy)
  DTSD_1352_SENSOR(export_active_energy)
  DTSD_1352_SENSOR(total_reactive_energy)
  DTSD_1352_SENSOR(import_reactive_energy)
  DTSD_1352_SENSOR(export_reactive_energy)
  DTSD_1352_SENSOR(active_power)
  DTSD_1352_SENSOR(reactive_power)
  DTSD_1352_SENSOR(apparent_power)
  DTSD_1352_SENSOR(voltage)
  DTSD_1352_SENSOR(current)
  DTSD_1352_SENSOR(power_factor)
  DTSD_1352_SENSOR(frequency)

  void update() override;

  void on_modbus_data(const std::vector<uint8_t> &data) override;

  void dump_config() override;
};

}  // namespace dtsd_1352
}  // namespace esphome
