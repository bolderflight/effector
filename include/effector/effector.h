/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_EFFECTOR_EFFECTOR_H_
#define INCLUDE_EFFECTOR_EFFECTOR_H_

#include <array>
#include <algorithm>
#include "core/core.h"
#include "sbus/sbus.h"
#include "types/types.h"
#include "polytools/polytools.h"

namespace effector {

template<std::size_t LEN>
class Effector {
 public:
  /* SBUS only */
  Effector(HardwareSerial *bus) : sbus_(bus), use_pwm_(false), use_sbus_(true) {}
  /* PWM only */
  Effector(const std::array<int, LEN> &pwm) : pwm_pins_(pwm), use_pwm_(true), use_sbus_(false) {}
  /* SBUS and PWM */
  Effector(HardwareSerial *bus, const std::array<int, LEN> &pwm) : sbus_(bus), pwm_pins_(pwm), use_pwm_(true), use_sbus_(true) {} 
  /* Setup effectors and begin communications */
  void Init() {
    /* SBUS */
    if (use_sbus_) {
      sbus_.Begin();
    }
    /* PWM */
    if (use_pwm_) {
      analogWriteResolution(PWM_RESOLUTION_BITS_);
      pwm_frequency_.fill(DEFAULT_PWM_FREQUENCY);
      pwm_period_.fill(1.0f /  DEFAULT_PWM_FREQUENCY  * 1000000.0f);
    }
  }
  /* Add an effector command */
  template<std::size_t SIZE>
  void AddCmd(const types::ActuatorCmd<SIZE> &act) {
    /* SBUS */
    if (act.actuator_type() == types::ActuatorCmd<SIZE>::SBUS) {
      if ((act.channel() >= 0) && (act.channel() < sbus_cmds_.size())) {
        sbus_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.deg());
      }
    }
    /* PWM */
    if (act.actuator_type() == types::ActuatorCmd<SIZE>::PWM) {
      if ((act.channel() >= 0) && (act.channel() < LEN)) {
        pwm_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.deg());
      }
    }
  }
  /* Send all commands to effectors */
  void Write() {
    /* Write SBUS packet */
    if (use_sbus_) {
      sbus_.tx_channels(sbus_cmds_);
      sbus_.Write();
    }
    /* Write PWM commands */
    if (use_pwm_) {
      for (size_t ch = 0; ch < LEN; ch++) {
        analogWrite(pwm_pins_[ch], pwm_cmds_[ch] / pwm_period_[ch] * PWM_RESOLUTION_);
      }
    }
  }

 private:
  /* Flags */
  bool use_pwm_, use_sbus_;
  /* SBUS object */
  actuators::Sbus sbus_;
  /* SBUS commands */
  std::array<uint16_t, 16> sbus_cmds_;
  /* PWM resolution */
  static constexpr int PWM_RESOLUTION_BITS_ = 16;
  static constexpr float PWM_RESOLUTION_ = std::pow(2.0f, static_cast<float>(PWM_RESOLUTION_BITS_)) - 1.0f;
  /* PWM pins */
  std::array<int, LEN> pwm_pins_;
  /* PWM pin frequency */
  std::array<float, LEN> pwm_frequency_;
  static constexpr float DEFAULT_PWM_FREQUENCY = 50;
  /* PWM pin period */
  std::array<float, LEN> pwm_period_;
  /* PWM commands */
  std::array<float, LEN> pwm_cmds_;
};

}  // namespace effector

#endif  // INCLUDE_EFFECTOR_EFFECTOR_H_
