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

#include "effector/effector.h"

/* Example class compiant with the effector interface */
template<std::size_t N>
class EffectorExample {
 public:
  bool Init(const bfs::EffectorConfig<N> &cfg) {}
  void Cmd(std::span<float> cmds) {}
  void Write() {}
  void EnableMotors() {}
  void DisableMotors() {}
  void EnableServos() {}
  void DisableServos() {}
};

/* Function that is templated against the Effector interface */
template<std::size_t N, bfs::Effector<N> T>
bool InitEffector(T effector, const bfs::EffectorConfig<N> &config) {
  return effector.Init(config);
}

/* Example effector config */
static constexpr std::size_t NUM_PWM_PINS = 5;
std::array<int8_t, NUM_PWM_PINS> PWM_PINS = {1, 2, 3, 4, 5};
bfs::EffectorConfig<NUM_PWM_PINS> config = {
  .hw = PWM_PINS,
  .effectors = {
    {
      .type = bfs::SERVO,
      .ch = 0,
      .min = -20,
      .max = 20,
      .failsafe = 0,
      .num_coef = 2,
      .poly_coef = {1, 0}
    },
    {
      .type = bfs::SERVO,
      .ch = 1,
      .min = -20,
      .max = 20,
      .failsafe = -5,
      .num_coef = 2,
      .poly_coef = {2, 0}
    }
  }
};

int main() {
  EffectorExample<NUM_PWM_PINS> pwm;
  bool status = InitEffector<NUM_PWM_PINS>(pwm, config);
}

