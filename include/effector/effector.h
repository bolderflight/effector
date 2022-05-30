/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2022 Bolder Flight Systems Inc
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

#include <concepts>
#include <optional>
#include <variant>
#include <array>
#include <cstdint>
#include "core/core.h"

namespace bfs {

inline constexpr int8_t MAX_NUM_EFFECTOR_CH = 32;
inline constexpr int8_t MAX_NUM_SBUS_CH = 16;

/* Effector config */
struct EffectorConfig {
  std::optional<int8_t> num_ch;
  std::variant<HardwareSerial *, std::array<int8_t, MAX_NUM_EFFECTOR_CH>> hw;
};
/* Effector command */
struct EffectorCmd {
  float cmd[MAX_NUM_EFFECTOR_CH];
};

template<typename T>
concept Effector = requires(T effector, const EffectorConfig &cfg,
                                        const EffectorCmd &cmds) {
  { effector.Config(cfg) } -> std::same_as<bool>;
  { effector.Init() } -> std::same_as<bool>;
  { effector.Cmd(cmds) } -> std::same_as<void>;
  { effector.Write() } -> std::same_as<void>;
};  // NOLINT - gets confused with concepts and semicolon after braces

}  // namespace bfs

#endif  // INCLUDE_EFFECTOR_EFFECTOR_H_
