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

#ifndef INCLUDE_EFFECTOR_EFFECTOR_H_
#define INCLUDE_EFFECTOR_EFFECTOR_H_

#include <array>
#include "polytools/polytools.h"

namespace bfs {
/* Effector types */
enum class EffectorType {
  SERVO,
  MOTOR
};
/* Defines an effector */
template<int N>
struct Effector {
  const EffectorType type;
  const int ch;
  const float failsafe;
  const std::size_t size;
  const std::array<float, N> cal_coeff;
  uint16_t Cmd(const float cmd) const {
    return Cmd(cmd, true, true);
  }
  uint16_t Cmd(const float cmd, const bool motor_en) const {
    return Cmd(cmd, true, motor_en);
  }
  uint16_t Cmd(const float cmd, const bool servo_en, const bool motor_en) const {
    if ((type == EffectorType::SERVO) && (servo_en)) {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, cmd));
    } else if ((type == EffectorType::SERVO) && (!servo_en)) {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, failsafe));
    } else if ((type == EffectorType::MOTOR) && (motor_en)) {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, cmd));
    } else {
      return static_cast<uint16_t>(polyval(cal_coeff.data(), size, failsafe));
    }
  }
};

}  // namespace bfs

#endif  // INCLUDE_EFFECTOR_EFFECTOR_H_
