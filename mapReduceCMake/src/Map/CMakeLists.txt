# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("mapTest")

# Set Parameters
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/bin/test")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/lib64/test")

# Create FileIO File List
set(FileIO_files 
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.cpp
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.h)

set(Map_files
${TOP_LEVEL_ROOT_DIR}/src/Map/Map.h
${TOP_LEVEL_ROOT_DIR}/src/Map/Map.cpp
"test/TestMap.h"
"test/TestMap.cpp")

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
${Map_files}
${FileIO_files})

target_include_directories(${PROJECT_NAME}
PRIVATE
${TOP_LEVEL_ROOT_DIR}/src/Map
#${TOP_LEVEL_ROOT_DIR}/src/Map/Test
${TOP_LEVEL_ROOT_DIR}/src/FileIO
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
