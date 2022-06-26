cmake_minimum_required(VERSION 3.9)
project(ClassVersion002
        VERSION 0.0.2
        DESCRIPTION "Library takes statics from Class V 002")

set(CMAKE_CXX_STANDARD 17)


include_directories(
	../../API/
)

add_library(LibVersion002lib SHARED
	../../API/ishared.h
	StatVersion002.h
	StatVersion002.cpp
)
