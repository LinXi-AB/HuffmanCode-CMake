add_executable(unit_test HuffmanCodecTest.cpp)
target_link_libraries(unit_test GTest::gtest_main HuffmanCodeLib)

## 引入GoogleTest模块
include(GoogleTest)

## 将GoogleTest注册到ctest
gtest_discover_tests(unit_test)