cmake_minimum_required(VERSION 3.16)
project(qt_test)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_AUTOMOC ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(qt_test main.cpp)
target_link_libraries(qt_test Qt6::Widgets)