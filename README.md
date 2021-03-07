# actuator
This library provides utility functions for interacting with actuators. 
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *actuator*. The header is added as:

```
#include "actuator/actuator.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library and example executable called *actuator_example*. The example executable source file is located at *examples/actuator_example.cc*.

# Namespaces
This library is within the namespace *bfs*

# Objects

**enum Type** This enum defines the type of actuator, options are a servo or a motor.

| Actuator Type | Enum Value |
| --- | --- |
| Servo | SERVO |
| Motor | MOTOR |

**Actuator<int N>** This struct defines an actuator object. Member variables are:
   * *Type type*: the actuator type
   * *int ch*: the actuator channel (i.e. PWM channel 0, SBUS channel 15, etc)
   * *float failsafe*: the actuator command when failsafed
   * *std::array<float, N> calibration_coeff*: polynomial coefficients taking the input command value (i.e. a surface angle command) to the output format (i.e. SBUS or PWM command)

Note that all of these member variables are constant and should be defined when the object is declared. The size of the *calibration_coeff* array is templated. 

```C++
bfs::Actuator<2> de = {
   .type = bfs::SERVO,
   .channel = 0,
   .failsafe = 0,
   .calibration_coeff = {1, 0}
};
```

# Methods

**uint16_t Cmd(const float cmd)** Given an angle command, computes the appropriate PWM or SBUS value using the actuator object polynomial coefficients. If the actuator object is a *MOTOR* type and motors are disabled, this function will output the failsafe command applied to the calibration polynomial. Similarly if a *SERVO* type and servos are disabled.

```C++
std::cout << de.Cmd(10) << std::endl;
```

By default, motors are disabled and servos are enabled.

**void EnableMotors()** Enables motors to output values.

**void DisableMotors()** Disables motor commands, using the failsafe value instead. Together with the *EnableMotors* function, this makes an effective throttle safety switch.

**void EnableServos()** Enables servos to output values.

**void DisableServos()** Disables servo commands, using the failsafe value instead. Together with the *EnableServos* function, this could be part of a lost link solution.
