cmake_minimum_required(VERSION 3.15)
project(ModernCppEngine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Engine library
file(GLOB_RECURSE ENGINE_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)
list(FILTER ENGINE_SOURCES EXCLUDE REGEX ".*/main\\.cpp$")

add_library(ModernCppEngine STATIC ${ENGINE_SOURCES})

target_include_directories(ModernCppEngine
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
           $<INSTALL_INTERFACE:include>
)

# Sample application
add_executable(ModernCppEngineApp src/main.cpp)
target_link_libraries(ModernCppEngineApp PRIVATE ModernCppEngine)

# Tests
enable_testing()
add_subdirectory(tests)
