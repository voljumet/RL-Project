cmake_minimum_required(VERSION 3.21)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp include/jsoncpp.cpp main.h printer.cpp printer.h battleclass.cpp battleclass.h)
include_directories(include)