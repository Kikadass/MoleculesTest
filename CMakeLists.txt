cmake_minimum_required(VERSION 3.2)
PROJECT(MoleculesTest)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS "-framework CoreFoundation -framework ApplicationServices")

ADD_SUBDIRECTORY(src)
