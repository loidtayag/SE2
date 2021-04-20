cmake_minimum_required(VERSION 3.17)
project(SE2 C)

set(CMAKE_C_STANDARD 11)

add_executable(SE2 main.c lib.c lib.h)