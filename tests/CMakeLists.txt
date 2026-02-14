# CMake configuration for tests

add_executable(MemPoolTests MemoryPoolTests.cpp)
add_executable(ECSTests ECSTests.cpp)

target_link_libraries(MemPoolTests PRIVATE ModernCppEngine)
target_link_libraries(ECSTests PRIVATE ModernCppEngine)

add_test(NAME MemPoolTests COMMAND MemPoolTests)
add_test(NAME ECSTests COMMAND ECSTests)
