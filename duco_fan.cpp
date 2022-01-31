#include "esphome.h"
#include "esphome/core/log.h"
#include "esphome/components/fan/fan_helpers.h"
#include "duco_fan.h"

namespace esphome {
namespace duco {

static const char *const TAG = "duco.fan";
DucoCC1101 rf;

void DucoFan::dump_config() {
  ESP_LOGCONFIG(TAG, "Fan '%s':", this->fan_->get_name().c_str());
}

void DucoFan::setup() {

  auto traits = fan::FanTraits(true, true, true, this->speed_count_);
  this->fan_->set_traits(traits);
  ESP_LOGE(TAG, "Fan setup");

  auto call = this->fan_->make_call();
  call.set_speed(true);
  this->fan_->add_on_state_callback([this]() { ESP_LOGE(TAG, "On state callback"); });

  rf.init();
  rf.initReceive();
  rf.setLogRFMessages(true);

  this->device_address = 6;
  int id[4] = {0x00, 0x02, 0x4e, 0x26};

  std::copy(id, id+4, this->network_id);

  if (device_address != 0) {
    rf.setDeviceAddress(device_address);
    rf.setNetworkId(network_id);
  }

  // register_service(&DucoFan::join, "join");
  // register_service(&DucoFan::leave, "leave");
  // register_service(&DucoFan::installer_mode, "installer_mode", {"mode"});  
}

// void installer_mode() {
//   ESP_LOGD("ducitho", "installer_mode %s", mode ? "true" : "false");
//   if(mode){
//     rf.enableInstallerMode();
//   }
//   else{
//     rf.disableInstallerMode();
//   }
// }

void join() {
  ESP_LOGD("ducitho", "Join");
  rf.sendJoinPacket();

  uint8_t addr = rf.getDeviceAddress();
  uint8_t* id = rf.getnetworkID();

  // memcpy(network_id, id, 4);
  // copy(id, id+4, network_id);

  ESP_LOGI("ducitho", "Joined with device address: %u and network ID: %x %x %x %x", addr, id[0], id[1], id[2], id[3]);
}

void leave() {
  ESP_LOGD("ducitho", "Leave");
  rf.sendDisjoinPacket();
}


// void DucoFan::update(){
//   ESP_LOGE(TAG, "Updating");
// }

void DucoFan::loop() {
  ESP_LOGE(TAG, "Looping");

  if (rf.checkForNewPacket()) {

    uint8_t numberOfLogMessages = rf.getNumberOfLogMessages();
    for(int i=0; i< numberOfLogMessages;i++){
      ESP_LOGD("ducitho", "Message: %s", rf.logMessages[i] );
    }
  }
  // if (!this->next_update_) {
  //   return;
  // }
  // this->next_update_ = false;

  // {
    float speed = 1.0f;
    if (this->fan_->state) {
      speed = static_cast<float>(this->fan_->speed) / static_cast<float>(this->speed_count_);
    }
    ESP_LOGD(TAG, "Setting speed: %.2f", speed);

    auto call = this->fan_->make_call();
    call.set_speed(speed);
  // }
}

float DucoFan::get_setup_priority() const { return setup_priority::DATA; }

}  // namespace duco
}  // namespace esphome