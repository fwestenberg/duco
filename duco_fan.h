#pragma once

// #include "esphome/core/component.h"
// #include "esphome/components/api/custom_api_device.h"
// #include "esphome/components/fan/fan_state.h"
#include "esphome.h"
#include "DucoCC1101.h"

namespace esphome {
namespace duco {

class DucoFan : public Component { //, public CustomAPIDevice {
 public:
  DucoFan(){}
  // DucoFan(fan::FanState *fan) : fan_(fan) {}

  void setup() override;
  void loop() override;
  // void update() override;
  void dump_config() override;

  // void installer_mode(bool mode);
  void join();
  void leave();

  float get_setup_priority() const override;

 protected:
  fan::FanState *fan_;
  // float FanSpeed = 1;
  // fan::FanSpeed *fan_;
  // output::FloatOutput *output_;
  // bool next_update_{true};
  int speed_count_ = 4;

  uint8_t device_address = 0;
  uint8_t network_id[4];
};

}  // namespace duco
}  // namespace esphome