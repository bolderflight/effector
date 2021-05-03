# effector
Defines a common interface for our effectors.
   * [License](LICENSE.md)
   * [Changelog](CHANGELOG.md)
   * [Contributing guide](CONTRIBUTING.md)

# Description
This library abstracts away effector hardware specifics by defining common configuration and data sturctures and an interface class defining common methods for effectors. This enables the designer of higher-level software to reference this class, rather than individual effector drivers, and have a fixed interface to design against.

## Installation
CMake is used to build this library, which is exported as a library target called *effector*. The header is added as:

```
#include "effector/effector.h"
```

The library can be also be compiled stand-alone using the CMake idiom of creating a *build* directory and then, from within that directory issuing:

```
cmake .. -DMCU=MK66FX1M0
make
```

This will build the library. Notice that the *cmake* command includes a define specifying the microcontroller the code is being compiled for. This is required to correctly configure the code, CPU frequency, and compile/linker options. The available MCUs are:
   * MK20DX128
   * MK20DX256
   * MK64FX512
   * MK66FX1M0
   * MKL26Z64
   * IMXRT1062_T40
   * IMXRT1062_T41

These are known to work with the same packages used in Teensy products. Also switching packages is known to work well, as long as it's only a package change.

## Namespace
This library is within the namespace *bfs*.

## Class / Methods

**enum EffectorType** Describes the type of effector.

| Name | Description |
| --- | --- |
| SERVO_PWM | A servo / actuator |
| MOTOR_PWM | A motor |

**struct EffectorChannel** defines the configuration for a single effector.

| Name | Description |
| --- | --- |
| EffectorType type | The effector type |
| int8_t ch | The effector channel number |
| float min | Minimum command  |
| float max | Maximum command |
| float failsafe | Failsafe commnd |
| int8_t num_coef | The number of polynomial coefficients |
| float poly_coef[MAX_POLY_COEF_SIZE] | Polynomial coefficients to convert an effector angle command to the raw command to send the servo or motor |

**struct EffectorConfig<std::size_t N>** defines the configuration for the *Effector* object. Templated by the number of effectors.

| Name | Description |
| --- | --- |
| std::variant<HardwareSerial *, std::array<int8_t, N>> hw | Either a pointer to a Serial port for SBUS or an array of pin numbers for PWM |
| EffectorChannel effectors[N] | Effector configuration | 

**Effector** Concepts are used to define what an *Effector* compliant object looks like and provide a means to templating against an *Effector* interface. The required methods are:

**bool Init(const EffectorConfig &cfg)** Configures and initializes the effectors given a reference to the *EffectorConfig* struct. Returns true on successfully initializing the effectors.

**void Cmd(std::span<float> cmd)** Sets the effector commands given a span of angle commands.

**void Write()** Sends the commands to the effectors.

**void EnableMotors()** Enables motor commands. If not enabled, the failsafe command is sent instead.

**void DisableMotors()** Disables motor commands.

**void EnableServos()** Enables servo commands. If not enabled, the failsafe command is sent instead.

**void DisableServos()** Disables servo commands.
