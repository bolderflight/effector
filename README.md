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

**struct EffectorConfig** defines a structure used to configure an effector. The data fields are:

| Name | Description |
| --- | --- |
| EffectorType type | The effector type |
| int8_t ch | The effector channel number |
| float min | Minimum command |
| float max | Maximum command |
| float failsafe | Failsafe command |
| std::vector<float> poly_coef | A vector of polynomial coefficients to convert an effector angle command to the raw command to send the servo or motor |

The effector type is an enum called *EffectorType*:

| Name | Description |
| --- | --- |
| SERVO | A servo / actuator |
| MOTOR | A motor |

**Effector** The *Effector* class defines a common interface to effectors. It is templated with the object implementing this interface for the desired sensor. It is also templated with the number of effectors of the specified object. For example, the SBUS implementation with 16 SBUS channels may be:

```C++
bfs::Effector<bfs::SbusTx, 16> effector(&Serial1);
```

Similar to how a pure virtual class can be used to define an interface using dynamic polymorphism, this approach uses static polymorphism.

**explicit Effector(HardwareSerial &ast;bus)** creates an effector object; a pointer to the Serial bus object is passed.

**explicit Effector(const std::array<int, N> &pins)** creates an effector object, an array of effector pins is passed.

**bool Init(const std::array<EffectorConfig, N> &ref)** initializes communication with the effectors and configures them given an array of EffectorConfig objects. Returns true if communication is established and configuration was successful.

**bool Cmd(const std::array<float, N> &cmds)** sets the effector commands given an array of angle commands.

**void Write()** writes the commands to the effectors.

**void EnableMotors(const bool val)** enables outputs from the motors if passed true, otherwise, uses the failsafe command. Defaults false.

**void EnableMotors(const bool val)** enables outputs from the servos if passed true, otherwise, uses the failsafe command. Defaults true.

