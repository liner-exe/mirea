cmake_minimum_required(VERSION 3.31)
project(SIAOD_6_2 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(SIAOD_6_2 6_2.cpp)

if (WIN32)
    target_link_options(SIAOD_6_2 PRIVATE -static-libgcc -static-libstdc++)
endif()