cmake_minimum_required(VERSION 3.23.2)

project(triangle-game-board)

add_library(${PROJECT_NAME} SHARED
	board.cpp peg.cpp
)


set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "board.h;peg.h")

install(TARGETS ${PROJECT_NAME} DESTINATION lib)