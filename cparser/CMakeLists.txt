cmake_minimum_required(VERSION 3.20)
project(cparser)

set(CMAKE_CXX_STANDARD 14)

add_executable(cparser
        main.cpp
        globals.h
        parse.cpp
        parse.h
        scan.cpp
        scan.h
        util.cpp
        util.h)
