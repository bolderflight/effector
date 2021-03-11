/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2021 Bolder Flight Systems Inc
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the “Software”), to
* deal in the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
* IN THE SOFTWARE.
*/

#ifndef INCLUDE_ACTUATOR_ACTUATOR_H_
#define INCLUDE_ACTUATOR_ACTUATOR_H_

#include <array>
#include "polytools/polytools.h"

namespace bfs {
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
  Type type;
  int ch;
  float failsafe;
  std::size_t size;
  std::array<float, N> cal_coeff;
  uint16_t Cmd(const float cmd) {
    if ((type == SERVO) && (internal::servo_enable_)) {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, cmd));
    } else if ((type == SERVO) && (!internal::servo_enable_)) {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, failsafe));
    } else if ((type == MOTOR) && (internal::motor_enable_)) {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, cmd));
    } else {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, failsafe));
    }
  }
};
/* Enable / disable motors */
void EnableMotors() {internal::motor_enable_ = true;}
void DisableMotors() {internal::motor_enable_ = false;}
/* Enable / disable servos */
void EnableServos() {internal::servo_enable_ = true;}
void DisableServos() {internal::servo_enable_ = false;}
}  // namespace bfs

#endif  // INCLUDE_ACTUATOR_ACTUATOR_H_
