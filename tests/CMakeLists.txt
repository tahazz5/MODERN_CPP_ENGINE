# CMake configuration for tests

# Use GoogleTest if available
find_package(GTest REQUIRED)

add_executable(MemPoolTests MemoryPoolTests.cpp)
add_executable(ECSTests ECSTests.cpp)

target_link_libraries(MemPoolTests PRIVATE GTest::gtest_main ModernCppEngine)
target_link_libraries(ECSTests PRIVATE GTest::gtest_main ModernCppEngine)

include(GoogleTest)
gtest_discover_tests(MemPoolTests)
gtest_discover_tests(ECSTests)
