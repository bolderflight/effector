# Changelog

## v7.0.0
- Simplified interface and expect that commands are received normalized +/-1

## v6.1.3
- std::optional doesn't work, since I'd like to use initializer lists, switching to a default ch value of -1 to check whether an EffectorChannel was set.

## v6.1.2
- Made EffectorChannel array std::optional so we can check if an effector has been configured.

## v6.1.1
- Updated to support global_defs v2.1.0

## v6.1.0
- Moved from Enum to plain old data types to ease integration with Simulink autocode

## v6.0.2
- Fixed constness of std::span

## v6.0.1
- Pull MAX_POLY_COEF_SIZE from global_defs

## v6.0.0
- Updated interface to use concepts

## v5.0.0
- Modified to be an interface class

## v4.1.1
- Added min and max limits

## v4.0.1
- Fixing const-ness of Cmd method

## v4.0.0
- Moved the servo and motor enable to inputs for the Cmd method
- Changed Type to EffectorType and made it an enum class for better type safety
- Renamed the library to effector instead of actuator to better match nomenclature used elsewhere.

## v3.0.0
- Added a size member to select the number of coefficients
- The template sets the max number of coefficients

## v2.0.0
- Updated namespace to *bfs*
- Updated to support polytools v2.0.0
- Moved the Cmd function to be a method in the *Actuator* struct

## v1.0.2
- Updated CONTRIBUTING
- Switched from ssh to https for *fetch_content*

## v1.0.1
- Updated license to MIT
- Specified version for dependencies

## v1.0.0
- Initial baseline
