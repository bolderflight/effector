# effector
This library provides utility functions for interacting with effectors. 
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

## Installation
CMake is used to build this library, which is exported as a library target called *effector*. The header is added as:

```
#include "effector/effector.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake ..
make
```

This will build the library and example executable called *effector_example*. The example executable source file is located at *examples/effector_example.cc*.

# Namespaces
This library is within the namespace *bfs*

# Objects

**enum class EffectorType** This enum defines the type of effector, options are a servo or a motor.

| Effector Type | Enum Value |
| --- | --- |
| Servo | SERVO |
| Motor | MOTOR |

**Effector<int N>** This struct defines an *effector* object. Member variables are:
   * *Type type*: the effector type
   * *int ch*: the effector channel (i.e. PWM channel 0, SBUS channel 15, etc)
   * *float failsafe*: the effector command when failsafed
   * *std::size_t size*: the number of calibration coefficients
   * *std::array<float, N> cal_coeff*: polynomial coefficients taking the input command value (i.e. a surface angle command) to the output format (i.e. SBUS or PWM command)

Note that all of these member variables are constant and should be defined when the object is declared. The maximum size of the *cal_coeff* array is templated. 

```C++
bfs::Effector<10> de = {
   .type = bfs::EffectorTypeSERVO,
   .channel = 0,
   .failsafe = 0,
   .size = 2,
   .calibration_coeff = {1, 0}
};
```

# Methods

**uint16_t Cmd(const float cmd, const bool servo_en, const bool motor_en)** Given an angle command, computes the appropriate PWM or SBUS value using the effector object polynomial coefficients. Also has inputs for setting whether the servo and motor are enabled. If the effector object is a *MOTOR* type and motors are disabled, this function will output the failsafe command applied to the calibration polynomial. Similarly if a *SERVO* type and servos are disabled.

```C++
std::cout << de.Cmd(10, true, true) << std::endl;
```

**uint16_t Cmd(const float cmd, const bool motor_en)** Given an angle command, computes the appropriate PWM or SBUS value using the effector object polynomial coefficients. Also has an input for setting whether motors are enabled. Servos are always enabled in this overload. If the effector object is a *MOTOR* type and motors are disabled, this function will output the failsafe command applied to the calibration polynomial.

```C++
std::cout << de.Cmd(10, false) << std::endl;
```

**uint16_t Cmd(const float cmd)** Given an angle command, computes the appropriate PWM or SBUS value using the effector object polynomial coefficients. Motors and servos are always enabled with this overload.

```C++
std::cout << de.Cmd(10) << std::endl;
```
