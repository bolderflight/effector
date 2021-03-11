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

#include <iostream>
#include "effector/effector.h"

int main() {

  /* Servo actuator */
  bfs::Effector<20> de = {
    .type = bfs::EffectorType::SERVO,
    .ch = 0,
    .failsafe = 0,
    .size = 2,
    .cal_coeff = {1, 0}
  };
  /* Motor actuator */
  bfs::Effector<20> throttle = {
    .type = bfs::EffectorType::MOTOR,
    .ch = 0,
    .failsafe = 0,
    .size = 2,
    .cal_coeff = {1, 0}
  };
  /* Print the command */
  std::cout << de.Cmd(10, true, false) << "\t" << throttle.Cmd(10, true, false) << std::endl;
  /* Enable the motor and print the command */
  std::cout << de.Cmd(10, true, true) << "\t" << throttle.Cmd(10, true, true) << std::endl;
  /* Disable the servo and print the command */
  std::cout << de.Cmd(10, false, true) << "\t" << throttle.Cmd(10, false, true) << std::endl;
  /* Disable the motors and print the command */
  std::cout << de.Cmd(10, false, false) << "\t" << throttle.Cmd(10, false, false) << std::endl;
}

