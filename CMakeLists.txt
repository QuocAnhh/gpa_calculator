cmake_minimum_required(VERSION 3.10)
project(cgpa_calculator 
        VERSION 1.0.0
        DESCRIPTION "CGPA Calculator Application"
        LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build: Debug Release RelWithDebInfo MinSizeRel" FORCE)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add include directory
include_directories(include)

# Define source files explicitly instead of using GLOB
# This ensures CMake properly reconfigures when files are added or removed
set(SOURCES
    src/main.cpp
    # Add all your source files here
    # src/calculator.cpp
    # src/grading.cpp
    # etc.
)

# Create executable
add_executable(cgpa_calculator ${SOURCES})

# Installation rules
install(TARGETS cgpa_calculator
        RUNTIME DESTINATION bin)

# Enable testing option
option(BUILD_TESTS "Build tests" OFF)
if(BUILD_TESTS)
    enable_testing()
    # Add test directory if it exists
    # add_subdirectory(tests)
endif()

# Add compile warnings
if(MSVC)
    target_compile_options(cgpa_calculator PRIVATE /W4)
else()
    target_compile_options(cgpa_calculator PRIVATE -Wall -Wextra)
endif()