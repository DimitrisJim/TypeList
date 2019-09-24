cmake_minimum_required(VERSION 3.14)
project(TypeList)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(TypeList
        main.cpp
        test_typelist.hpp
        Typelist.hpp)
