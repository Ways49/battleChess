cmake_minimum_required(VERSION 3.28)
project(src)

IF (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "-static")
ENDIF()

#set(CMAKE_CXX_FLAGS -O3)
set(CMAKE_CXX_STANDARD 14)

add_executable(src
        main.cpp
        base.hpp
        monster.hpp
        experiment.hpp)
