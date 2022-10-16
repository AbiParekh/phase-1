# CMakeList.txt : CMake project for mapReduceCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CXX_STANDARD 17)

project ("mapReduceCMake")

# Set Parameters
set(TOP_LEVEL_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/lib64")

# Include FileIO
set(FileIO_src ${TOP_LEVEL_ROOT_DIR}/FileIO/fileIO.cpp)
set(FileIO_header ${TOP_LEVEL_ROOT_DIR}/FileIO/fileIO.h)

# Include Top Level Application
set(${PROJECT_NAME}_src ${TOP_LEVEL_ROOT_DIR}/mapReduceCmake.cpp)
set(${PROJECT_NAME}_header ${TOP_LEVEL_ROOT_DIR}/mapReduceCmake.h)

# Add source to this project's executable.
add_executable (mapReduceCMake 
${${PROJECT_NAME}_src}
${${PROJECT_NAME}_header}
${FileIO_src}
${FileIO_header})

target_include_directories(${PROJECT_NAME}
PRIVATE
${TOP_LEVEL_ROOT_DIR}/FileIO)

target_compile_definitions(${PROJECT_NAME}
PRIVATE 
-DPRINT_DEBUG)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
# TODO: Add tests and install targets if needed.

# add_subdirectroy(FileIO/test)
