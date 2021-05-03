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

#include <span>
#include <optional>
#include <variant>
#include <array>
#include <vector>
#include "core/core.h"
#include "global_defs/global_defs.h"

namespace bfs {

enum EffectorType : int8_t {
  SERVO = 0,
  MOTOR = 1
};
/* Config for a single effector */
struct EffectorChannel {
  EffectorType type;
  int8_t ch;
  float min;
  float max;
  float failsafe;
  int8_t num_coef;
  float poly_coef[MAX_POLY_COEF_SIZE];
};
/* Effector config, templated with number of effectors */
template<std::size_t N>
struct EffectorConfig {
  std::variant<HardwareSerial *, std::array<int8_t, N>> hw;
  EffectorChannel effectors[N];
};

template<typename T, std::size_t N>
concept Effector = requires(T effector,
                            const EffectorConfig<N> &cfg,
                            std::span<float> cmds) {
  { effector.Init(cfg) } -> std::same_as<bool>;
  { effector.Cmd(cmds) } -> std::same_as<void>;
  { effector.Write() } -> std::same_as<void>;
  { effector.EnableMotors() } -> std::same_as<void>;
  { effector.DisableMotors() } -> std::same_as<void>;
  { effector.EnableServos() } -> std::same_as<void>;
  { effector.DisableServos() } -> std::same_as<void>;
};  // NOLINT - gets confused with concepts and semicolon after braces

}  // namespace bfs

#endif  // INCLUDE_EFFECTOR_EFFECTOR_H_
