#pragma once

namespace esphome {
namespace dtsd_1352 {

static const float TWO_DEC_UNIT = 0.01;
static const float ONE_DEC_UNIT = 0.1;
static const float NO_DEC_UNIT = 1;
static const float MULTIPLY_TEN_UNIT = 10;
static const float MULTIPLY_THOUSAND_UNIT = 1000;

/* PHASE STATUS REGISTERS */
static const uint16_t DTSD_TOTAL_ACTIVE_ENERGY = 0x0000;
static const uint16_t DTSD_IMPORT_ACTIVE_ENERGY = 0x000A;
static const uint16_t DTSD_EXPORT_ACTIVE_ENERGY = 0x0014;
static const uint16_t DTSD_TOTAL_REACTIVE_ENERGY = 0x001E;
static const uint16_t DTSD_IMPORT_REACTIVE_ENERGY = 0x0028;
static const uint16_t DTSD_EXPORT_REACTIVE_ENERGY = 0x0032;
static const uint16_t DTSD_ACTIVE_POWER = 0x016A;
static const uint16_t DTSD_REACTIVE_POWER = 0x0172;
static const uint16_t DTSD_APPARENT_POWER = 0x017A;
static const uint16_t DTSD_VOLTAGE = 0x0061;
static const uint16_t DTSD_CURRENT = 0x0064;
static const uint16_t DTSD_POWER_FACTOR = 0x017F;
static const uint16_t DTSD_FREQUENCY = 0x0077;

}  // namespace dtsd_1352
}  // namespace esphome
