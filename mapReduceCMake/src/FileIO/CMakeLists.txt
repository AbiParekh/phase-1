# CMakeList.txt : CMake project for mapReduceCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CXX_STANDARD 17)

project ("fileIOTest")

# Set Parameters

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/lib64")

# Create FileIO File List
set(FileIO_files 
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.cpp
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.h
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIOTester.cpp)

# Add source to this project's executable.
add_executable (${PROJECT_NAME} 
${FileIO_files}
)

target_include_directories(${PROJECT_NAME}
PRIVATE
${TOP_LEVEL_ROOT_DIR}/src/FileIO
)

target_compile_definitions(${PROJECT_NAME}
PRIVATE 
-DPRINT_DEBUG)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

