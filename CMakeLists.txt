cmake_minimum_required(VERSION 3.13)
if (DEFINED MCU)
	# Setting up the toolchain
	set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/cmake/cortex.cmake")
endif()
# Project information
project(Effector
	VERSION 1.0
	DESCRIPTION "Effector"
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
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/core.git
	)
	FetchContent_MakeAvailable(core)
	# Fetch sbus
	FetchContent_Declare(
		sbus
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/sbus.git
	)
	FetchContent_MakeAvailable(sbus)
	# Fetch types
	FetchContent_Declare(
		types
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/types.git
	)
	FetchContent_MakeAvailable(types)	
	# Fetch polytools
	FetchContent_Declare(
		polytools
		GIT_REPOSITORY 	git@gitlab.com:bolderflight/software/polytools.git
	)
	FetchContent_MakeAvailable(polytools)	
	# Add the library target
	add_library(effector INTERFACE)
	# Link libraries
	target_link_libraries(effector
		INTERFACE
			core
			sbus
			types
			polytools
	)
	# Setup include directories 
	target_include_directories(effector INTERFACE include/)
endif()
# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	if (DEFINED MCU)
		# Add the example target
		add_executable(effector_example examples/effector_example.cc)
		# Add the includes
		target_include_directories(effector_example PUBLIC 
			$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
			$<INSTALL_INTERFACE:include>
		)
		# Link libraries to the example target
		target_link_libraries(effector_example
			PRIVATE 
				effector
		)
		# Add hex and upload targets
		include(${CMAKE_SOURCE_DIR}/cmake/flash_mcu.cmake)
		FlashMcu(effector_example ${MCU})
	endif()
endif()
