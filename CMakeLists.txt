cmake_minimum_required(VERSION 3.10)

project(Huffmanzip)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(CompressCore CompressCore.cpp)
add_library(Settings Settings.cpp)
add_library(Util Util.cpp)
add_executable(huffmanzip huffmanzip.cpp)

target_link_libraries(huffmanzip PUBLIC CompressCore)
target_link_libraries(huffmanzip PUBLIC Settings)
target_link_libraries(huffmanzip PUBLIC Util)
