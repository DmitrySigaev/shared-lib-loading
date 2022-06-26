cmake_minimum_required(VERSION 3.9)
project(ClassVersion001
        VERSION 0.0.1
        DESCRIPTION "Library takes statics from Class V 001")

set(CMAKE_CXX_STANDARD 17)


include_directories(
	../../API/
)

add_library(LibVersion001 SHARED
	../../API/ishared.h
	StatVersion001.h
	StatVersion001.cpp
)
