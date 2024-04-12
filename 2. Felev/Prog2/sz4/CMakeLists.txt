cmake_minimum_required(VERSION 3.13)
project(sz4)

set(CMAKE_CXX_STANDARD 14)

include_directories(sz4)
include_directories(sz4/Debug)

add_executable(sz4
        sz4/Debug/sz4.pch
        sz4/stdafx.cpp
        sz4/stdafx.h
        sz4/sz4.cpp
        sz4/targetver.h)
