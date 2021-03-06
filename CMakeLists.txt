cmake_minimum_required(VERSION 3.13)
if (DEFINED MCU)
	# Setting up the toolchain
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/cortex.cmake")
endif()
# Project information
project(Effector
	VERSION 6.1.3
	DESCRIPTION "Effector interface"
	LANGUAGES CXX
)
if (DEFINED MCU)
	# Grab the processor and set up definitions and compile options
	include(${CMAKE_SOURCE_DIR}/cmake/config_mcu.cmake)
	configMcu(${MCU})
	include(FetchContent)
	# Fetch core
	FetchContent_Declare(
		core
		GIT_REPOSITORY https://github.com/bolderflight/core.git
		GIT_TAG v2.0.5
	)
	FetchContent_MakeAvailable(core)
	# Fetch global defs
	FetchContent_Declare(
		global_defs
		GIT_REPOSITORY https://github.com/bolderflight/global_defs.git
		GIT_TAG v2.1.0
	)
	FetchContent_MakeAvailable(global_defs)
	# Add the library target
	add_library(effector INTERFACE)
	# Link libraries
	target_link_libraries(effector
		INTERFACE
			core
			global_defs
	)
	# Setup include directories 
	target_include_directories(effector INTERFACE include/)
endif()
# Example if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	if (DEFINED MCU)		
		# Add the spi example target
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
		include(${CMAKE_SOURCE_DIR}/cmake/flash_mcu.cmake)
		FlashMcu(example ${MCU})
	endif()
endif()
