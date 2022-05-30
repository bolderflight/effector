[![Pipeline](https://gitlab.com/bolderflight/software/effector/badges/main/pipeline.svg)](https://gitlab.com/bolderflight/software/effector/) [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

![Bolder Flight Systems Logo](img/logo-words_75.png)

# Effector
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

This will build the library and an example called *example*, which has source code located in *examples/example.cc*. Notice that the *cmake* command includes a define specifying the microcontroller the code is being compiled for. This is required to correctly configure the code, CPU frequency, and compile/linker options. The available MCUs are:
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

**inline constexpr int8_t MAX_NUM_EFFECTOR_CH** defines the maximum number of effector channels from any one interface, currently set to 32.

**inline constexpr int8_t MAX_NUM_SBUS_CH** defines the maximum number of effector channels available from SBUS, currently set to 16.

**struct EffectorConfig** defines the configuration for the *Effector* object.

| Name | Description |
| --- | --- |
| std::optional<int8_t> num_ch | The number of effector channels. Currently ignored by SBUS effectors, which allow up to MAX_NUM_SBUS_CH of channels, but necessary for configuring PWM effectors. |
| std::variant<HardwareSerial *, std::array<int8_t, MAX_NUM_EFFECTOR_CH>> hw | Either the hardware serial port used for SBUS effectors or an array pins to be used for PWM effectors |

**struct EffectorCmd** defines a struct for setting the effector commands.

| Name | Description |
| --- | --- |
| float cmd[MAX_NUM_EFFECTOR_CH] | Effector commands, normalized to +/-1 |

**Effector** Concepts are used to define what an *Effector* compliant object looks like and provide a means to templating against an *Effector* interface. The required methods are:

**bool Config(const EffectorConfig &cfg)** Sets the effector configuration. Note that this should just set the configuration options in the effector driver, the configuration is actually applied to the effectors in the *Init* method. Configuration options should be checked for validity. True is returned on receiving a valid configuration, false on an invalid configuration.

**bool Init()** This method should establish communication and configure the effectors. True is returned on successfully initializing the effectors.

**void Cmd(const EffectorCmd &cmds)** Sets the effector commands.

**void Write()** Sends the commands to the effectors.
