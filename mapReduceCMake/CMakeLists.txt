# CMakeList.txt : CMake project for mapReduceCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("mapReduceCMake")

set(CXX_STANDARD 17)

set(TOP_LEVEL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

#TODO ADD TEST
add_subdirectory(src)
