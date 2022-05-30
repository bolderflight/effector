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

#include "effector/effector.h"

/* Example class compiant with the effector interface */
class EffectorExample {
 public:
  bool Config(const bfs::EffectorConfig &cfg) {}
  bool Init();
  void Cmd(const bfs::EffectorCmd &cmds) {}
  void Write() {}
};

/* Checking that SensorExample class meets the requirements of bfs::Effector */
static_assert(bfs::Effector<EffectorExample>,
  "Sensor example should conform to the effector interface");

/* Function that is templated against the Effector interface */
template<bfs::Effector T>
bool InitEffector(T effector, const bfs::EffectorConfig &config) {
  return effector.Config(config);
}

int main() {}
