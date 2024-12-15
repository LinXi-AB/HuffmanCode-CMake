# CMake最低版本
cmake_minimum_required(VERSION 3.8)

# 项目名称
project(HuffmanCode)

# C++标准使用20
set(CMAKE_CXX_STANDARD 20)

# 指定可执行文件生成路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# 添加头文件目录
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)

# 添加cpp文件
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

# 生成exe文件
add_executable(HuffmanCode ${SOURCES})