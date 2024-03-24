cmake_minimum_required(VERSION 3.19)
project(QuadTree)

set(CMAKE_CXX_STANDARD 14)

add_executable(QuadTree main.cpp QuadTree.cpp QuadTree.h Vector.cpp Vector.h Point.h AutoTests.cpp AutoTests.h)