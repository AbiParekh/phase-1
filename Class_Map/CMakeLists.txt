# CMakeList.txt : CMake project for MapReduce_CMake_Project1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

#project ("MapReduce_CMake_Project1")
project ("phase-1")

# Add source to this project's executable.
add_executable (Class_Map  "src/Map.cpp" "src/TestMap.cpp" "src/TestMap.h" "src/Map.h" "src/FileIO.cpp" "src/FileIO.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Class_Map PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
install (TARGETS Class_Map DESTINATION "Class_Map/bin" )
