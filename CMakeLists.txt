cmake_minimum_required(VERSION 3.0)
project(ETU)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(ETU main.cpp lab1.cpp BaseConvert.cpp BaseConvert.h lab2.cpp labs.h lab3.cpp ConsoleInteractor.cpp ConsoleInteractor.h lab4.cpp)
add_executable(LAB4 main.cpp labs.h lab4.cpp ConsoleInteractor.h ConsoleInteractor.cpp)
