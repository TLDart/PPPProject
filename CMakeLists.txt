cmake_minimum_required(VERSION 3.14)
project(Project_Test C)

set(CMAKE_C_STANDARD 90)

add_executable(Project_Test main.c user.c user.h)