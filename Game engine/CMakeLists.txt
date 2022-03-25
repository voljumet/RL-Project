cmake_minimum_required(VERSION 3.21)
project(Project)

set(CMAKE_CXX_STANDARD 14)

add_executable(Project main.cpp json/json.h json/allocator.h json/assertions.h json/config.h json/forwards.h json/json_features.h json/reader.h json/value.h json/version.h json/writer.h)

