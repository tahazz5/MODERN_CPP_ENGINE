cmake_minimum_required(VERSION 3.15)
project(ModernCppEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Engine library

file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
add_library(ModernCppEngine STATIC ${ENGINE_SOURCES})

target_include_directories(ModernCppEngine
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
           $<INSTALL_INTERFACE:include>
)

# Users can add additional source files in subdirectories; they're already
# picked up by the glob above.

# Tests
enable_testing()
add_subdirectory(tests)
