cmake_minimum_required(VERSION 3.0)
project(ETU)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

add_executable(ETU main.cpp lab1.cpp BaseConvert.cpp BaseConvert.h lab2.cpp labs.h lab3.cpp ConsoleInteractor.cpp ConsoleInteractor.h lab4.cpp)
add_executable(LAB4 main.cpp labs.h lab4.cpp ConsoleInteractor.h ConsoleInteractor.cpp)
add_executable(LAB5 main.cpp labs.h lab5.cpp)
