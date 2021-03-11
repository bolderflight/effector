# Changelog

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
