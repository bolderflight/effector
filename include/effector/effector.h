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
#include <vector>
#include "Core/core.h"

namespace bfs {

enum class EffectorType {
  SERVO,
  MOTOR
};
struct EffectorConfig {
  EffectorType type;
  int8_t ch;
  float min;
  float max;
  float failsafe;
  std::vector<float> poly_coef;
};
template<class Impl, std::size_t N>
class Effector {
 public:
  explicit Effector(HardwareSerial *bus) : impl_(bus) {}
  explicit Effector(const std::array<int, N> &pins) : impl_(pins) {}
  bool Init(const std::array<EffectorConfig, N> &ref) {return impl_.Init(ref);}
  bool Cmd(const std::array<float, N> &cmds) {return impl_.Cmd(cmds);}
  void Write() {impl_.Write();}
  void EnableMotors(const bool val) {impl_.EnableMotors(val);}
  void EnableServos(const bool val) {impl_.EnableServos(val);}

 private:
  Impl impl_;
};

}  // namespace bfs

#endif  // INCLUDE_EFFECTOR_EFFECTOR_H_
