cmake_minimum_required(VERSION 3.31)
project(SIAOD_6_1 CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(SIAOD_6_1 6_1.cpp
        HashTable.h
        HashTable.cpp
        Specialization.h)

if (WIN32)
    target_link_options(SIAOD_6_1 PRIVATE -static-libgcc -static-libstdc++)
    target_link_options(SIAOD_6_1 PRIVATE -static -lwinpthread)
endif()