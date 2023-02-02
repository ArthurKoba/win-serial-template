cmake_minimum_required(VERSION 3.23)
project(win_serial_template)

set(CMAKE_CXX_STANDARD 17)

add_executable(win_serial_template src/main.cpp src/serial.cpp src/serial.h)
