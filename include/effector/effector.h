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
      pwm_period_.fill(1.0f /  DEFAULT_PWM_FREQUENCY * 1000000.0f);
    }
  }
  /* Enable / disable motors and actuators */
  void enable_motors() {enable_motor_ = true;}
  void disable_motors() {enable_motor_ = false;}
  void enable_actuators() {enable_act_ = true;}
  void disable_actuators() {enable_act_ = false;}
  /* Add an effector command */
  template<std::size_t SIZE>
  void AddCmd(const types::EffectorCmd<SIZE> &act) {
    /* SBUS */
    if ((act.effector_type() == types::EffectorCmd<SIZE>::SBUS) && (use_sbus_)) {
      if ((act.channel() >= 0) && (act.channel() < sbus_cmds_.size())) {
        if (enable_act_) {
          sbus_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.deg());
        } else {
          sbus_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.safe());
        }
      }
    }
    /* PWM */
    if ((act.effector_type() == types::EffectorCmd<SIZE>::PWM) && (use_pwm_)) {
      if ((act.channel() >= 0) && (act.channel() < LEN)) {
        if (enable_act_) {
          pwm_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.deg());
        } else {
          pwm_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.safe());
        }
      }
    }
    /* SBUS Motor */
    if ((act.effector_type() == types::EffectorCmd<SIZE>::SBUS_MOTOR) && (use_sbus_)) {
      if ((act.channel() >= 0) && (act.channel() < sbus_cmds_.size())) {
        if (enable_motor_) {
          sbus_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.deg());
        } else {
          sbus_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.safe());
        }
      }
    }
    /* PWM Motor */
    if ((act.effector_type() == types::EffectorCmd<SIZE>::PWM_MOTOR) && (use_pwm_)) {
      if ((act.channel() >= 0) && (act.channel() < LEN)) {
        if (enable_motor_) {
          pwm_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.deg());
        } else {
          pwm_cmds_[act.channel()] = polytools::polyval(act.calibration_coeff(), act.safe());
        }
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
  bool enable_motor_ = false;
  bool enable_act_ = true;
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
