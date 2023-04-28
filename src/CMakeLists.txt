cmake_minimum_required(VERSION 3.23.2)
# Confirm CMake to use the new policy in terms of versioning
cmake_policy(SET CMP0048 NEW)

PROJECT(triangle-game)

SET(BUILD_SHARED_LIBS ON)


# Compiler Setup
SET(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

MESSAGE("SYSTEM_PROCESSOR: " ${ARCH})
MESSAGE("CXX COMPILER: " ${CMAKE_CXX_COMPILER})
MESSAGE("C COMPILER: " ${CMAKE_C_COMPILER})
MESSAGE("SYSTEM NAME: " ${CMAKE_SYSTEM_NAME})
MESSAGE("BUILD TYPE: " ${CMAKE_BUILD_TYPE})

add_subdirectory(board)
add_subdirectory(game)
add_subdirectory(external)

include_directories(include)