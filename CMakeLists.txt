cmake_minimum_required(VERSION 3.12)
project(BORK)

set(CMAKE_CXX_STANDARD 14)

add_executable(BORK main.cpp Room.cpp Room.h Item.cpp Item.h Character.cpp Character.h Die.cpp Die.h Dishes.cpp Dishes.h)