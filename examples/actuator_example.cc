/*
* Brian R Taylor
* brian.taylor@bolderflight.com
* 
* Copyright (c) 2020 Bolder Flight Systems
*/

#include <iostream>
#include "actuator/actuator.h"

int main() {

  /* Servo actuator */
  actuators::Actuator<2> de = {
    .type = actuators::SERVO,
    .channel = 0,
    .failsafe = 0,
    .calibration_coeff = {1, 0}
  };
  /* Motor actuator */
  actuators::Actuator<2> throttle = {
    .type = actuators::MOTOR,
    .channel = 0,
    .failsafe = 0,
    .calibration_coeff = {1, 0}
  };
  /* Print the command */
  std::cout << actuators::Cmd(de, 10) << "\t" << actuators::Cmd(throttle, 10) << std::endl;
  /* Enable the motor and print the command */
  actuators::EnableMotors();
  std::cout << actuators::Cmd(de, 10) << "\t" << actuators::Cmd(throttle, 10) << std::endl;
  /* Disable the servo and print the command */
  actuators::DisableServos();
  std::cout << actuators::Cmd(de, 10) << "\t" << actuators::Cmd(throttle, 10) << std::endl;
  /* Disable the motors and print the command */
  actuators::DisableMotors();
  std::cout << actuators::Cmd(de, 10) << "\t" << actuators::Cmd(throttle, 10) << std::endl;
}

