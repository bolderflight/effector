cmake_minimum_required(VERSION 3.13)
# Project information
project(Actuator
	VERSION 1.0.2
	DESCRIPTION "Actuator utility functions"
	LANGUAGES CXX
)
include(FetchContent)
# Fetch polytools
FetchContent_Declare(
	polytools
	GIT_REPOSITORY 	https://gitlab.com/bolderflight/software/polytools.git
	GIT_TAG v1.0.3
)
FetchContent_MakeAvailable(polytools)	
# Add the library target
add_library(actuator INTERFACE)
# Link libraries
target_link_libraries(actuator
	INTERFACE
		polytools
)
# Setup include directories 
target_include_directories(actuator INTERFACE include/)

# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	# Add the example target
	add_executable(actuator_example examples/actuator_example.cc)
	# Add the includes
	target_include_directories(actuator_example PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the example target
	target_link_libraries(actuator_example
		PRIVATE 
			actuator
	)
endif()
