cmake_minimum_required(VERSION 3.23.2)


# Setting up Project Name
SET(PROJ_NAME triangle-game)
SET(PROJECT_DESC "A Simple Implmentation of the Triangle Game")
SET(SHORT_PROJECT_DESC "Triangle Game 2")

# Project Versioning 
SET(VERSION_MAJOR 2)
SET(VERSION_MINOR 1)
SET(VERSION_FEATURE 0)
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_FEATURE}")
MESSAGE("VERSION: " ${VERSION})


PROJECT(${PROJ_NAME} VERSION ${VERSION})


configure_file(triangle-game-config.h.in triangle-game-config.h)

add_executable(${PROJECT_NAME} main.cpp)



target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC board)

target_link_directories(triangle-game-board PRIVATE ${PROJECT_BINARY_DIR}/board)

target_link_libraries(${PROJECT_NAME} PRIVATE triangle-game-board)



install(TARGETS ${PROJECT_NAME} DESTINATION bin)