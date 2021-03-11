cmake_minimum_required(VERSION 3.13)
# Project information
project(Effector
	VERSION 4.0.1
	DESCRIPTION "Effector utility functions"
	LANGUAGES CXX
)
include(FetchContent)
# Fetch polytools
FetchContent_Declare(
	polytools
	GIT_REPOSITORY https://github.com/bolderflight/polytools.git
	GIT_TAG v2.0.1
)
FetchContent_MakeAvailable(polytools)	
# Add the library target
add_library(effector INTERFACE)
# Link libraries
target_link_libraries(effector
	INTERFACE
		polytools
)
# Setup include directories 
target_include_directories(effector INTERFACE include/)

# Example and test if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
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
endif()
