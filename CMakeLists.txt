cmake_minimum_required(VERSION 3.27)
project(Three_Way_Quick_Sort_C___)

set(CMAKE_CXX_STANDARD 17)

add_executable(Three_Way_Quick_Sort_C___ main.cpp
        ThreeWayQuickSort.h
        InsertionSort.h
        QuickTester.h "InstrumentationTimer.h")
