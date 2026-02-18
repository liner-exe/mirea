cmake_minimum_required(VERSION 3.31)
set(PROJECT_NAME SIAOD_8_1_2)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 8_1_2.cpp)

file(GLOB_RECURSE HEADERS CONFIGURE_DEPENDS "*.h")
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "*.cpp")
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${HEADERS} ${SOURCES})

add_library(ProjectFiles ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PUBLIC ProjectFiles)

if (WIN32)
    target_link_options(${PROJECT_NAME} PRIVATE -static-libgcc -static-libstdc++)
endif()