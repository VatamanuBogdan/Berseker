cmake_minimum_required(VERSION 3.1)

add_library(stb src/stb_image.cpp)

target_include_directories(stb PUBLIC include/)