cmake_minimum_required(VERSION 3.14)

project(HuffmanCode)

## C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

## 没有这两行代码MSVC会报错
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")

## GoogleTest单元测试
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)
enable_testing()

## 全局头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

## 添加并构建子目录
add_subdirectory(src)
add_subdirectory(tests)
