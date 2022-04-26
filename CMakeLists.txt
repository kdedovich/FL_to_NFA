cmake_minimum_required(VERSION 3.12)
project(FL_Practic1)

set(CMAKE_CXX_STANDARD 17)
include_directories(${FL_Practic1_SOURCE_DIR})
add_executable(
        FL_Practic1
        NFA.h
        NFA.cpp
        gtest/gtest.h
        gtest/gtest-all.cc
        gtest/gtest_main.cc
        test.cpp
)

