# v3.14 required for FetchContent_MakeAvailable
cmake_minimum_required(VERSION 3.14)
if (DEFINED MCU)
  include(FetchContent)
  FetchContent_Declare(
    mcu_support
    GIT_REPOSITORY https://github.com/bolderflight/mcu-support.git
    GIT_TAG v1.0.0
  )
  FetchContent_MakeAvailable(mcu_support)
  # Setting up the toolchain
  set(CMAKE_TOOLCHAIN_FILE "${mcu_support_SOURCE_DIR}/cmake/cortex.cmake")
  # Project information
  project(Effector
    VERSION 7.0.0
    DESCRIPTION "Effector interface"
    LANGUAGES CXX
  )
  # Grab the processor and set up definitions and compile options
  include(${mcu_support_SOURCE_DIR}/cmake/config_mcu.cmake)
  configMcu(${MCU} ${mcu_support_SOURCE_DIR})
  # Fetch core
  FetchContent_Declare(
    core
    GIT_REPOSITORY https://github.com/bolderflight/core.git
    GIT_TAG v3.0.2
  )
  FetchContent_MakeAvailable(core)
  # Add the library target
  add_library(effector INTERFACE)
  # Link libraries
  target_link_libraries(effector
    INTERFACE
      core
  )
  # Setup include directories 
  target_include_directories(effector INTERFACE include/)
  # Need C++20
  target_compile_options(effector INTERFACE -std=c++20)

  # Example if this project is built separately
  if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
    # Add the example target
    add_executable(example examples/example.cc)
    # Add the includes
    target_include_directories(example PUBLIC 
      $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
      $<INSTALL_INTERFACE:include>
    )
    # Link libraries to the example target
    target_link_libraries(example
      PRIVATE 
        effector
    )
    # Add hex and upload targets
    include(${mcu_support_SOURCE_DIR}/cmake/flash_mcu.cmake)
    FlashMcu(example ${MCU} ${mcu_support_SOURCE_DIR})
  endif()
endif()
