cmake_minimum_required(VERSION 3.12)
project(TypeList)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(TypeList
        main.cpp
        test/test_typelist.hpp
        include/Typelist.hpp)
