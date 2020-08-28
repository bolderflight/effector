/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#ifndef INCLUDE_ACTUATOR_ACTUATOR_H_
#define INCLUDE_ACTUATOR_ACTUATOR_H_

#include <array>
#include "polytools/polytools.h"

namespace actuators {
namespace internal {
/* motor enable / disable state */
bool motor_enable_ = false;
/* servo enable / disable state */
bool servo_enable_ = true;
}  // namespace internal
/* Actuator types */
enum Type {
  SERVO,
  MOTOR
};
/* Defines an actuator */
template<int N>
struct Actuator {
  const Type type;
  const int channel;
  const float failsafe;
  const std::array<float, N> calibration_coeff;
};
/* Generate a command */
template<int N>
uint16_t Cmd(const Actuator<N> &ref, const float cmd) {
  if ((ref.type == SERVO) && (internal::servo_enable_)) {
    return static_cast<uint16_t>(polytools::polyval(ref.calibration_coeff, cmd));
  } else if ((ref.type == SERVO) && (!internal::servo_enable_)) {
    return static_cast<uint16_t>(polytools::polyval(ref.calibration_coeff, ref.failsafe));
  } else if ((ref.type == MOTOR) && (internal::motor_enable_)) {
    return static_cast<uint16_t>(polytools::polyval(ref.calibration_coeff, cmd));
  } else {
    return static_cast<uint16_t>(polytools::polyval(ref.calibration_coeff, ref.failsafe));
  }
}
/* Enable / disable motors */
void EnableMotors() {internal::motor_enable_ = true;}
void DisableMotors() {internal::motor_enable_ = false;}
/* Enable / disable servos */
void EnableServos() {internal::servo_enable_ = true;}
void DisableServos() {internal::servo_enable_ = false;}
}  // namespace actuators

#endif  // INCLUDE_ACTUATOR_ACTUATOR_H_
