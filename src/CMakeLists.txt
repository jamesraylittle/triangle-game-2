cmake_minimum_required(VERSION 3.23.2)

project (Triangle-Game-2.0)

include_directories(include)

file(GLOB SOURCES "*.cpp")

add_executable(tri-game ${SOURCES})