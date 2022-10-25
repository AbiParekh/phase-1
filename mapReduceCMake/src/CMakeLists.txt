# CMakeList.txt : CMake project for mapReduceCMake, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set(CXX_STANDARD 17)

project ("mapReducer")

# Set Parameters

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG "${TOP_LEVEL_ROOT_DIR}/build/lib64")

# Create FileIO File List
set(FileIO_files 
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.cpp
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.h)

set(Sorter_files
${TOP_LEVEL_ROOT_DIR}/src/Sorter/MapReduceSorter.h
${TOP_LEVEL_ROOT_DIR}/src/Sorter/MapReduceSorter.cpp)

#set(Reducer_files
#${TOP_LEVEL_ROOT_DIR}/src/ReduceClass/Reduce.h
#${TOP_LEVEL_ROOT_DIR}/src/ReduceClass/Reduce.cpp)

set(Map_files
${TOP_LEVEL_ROOT_DIR}/src/Map/Map.h
${TOP_LEVEL_ROOT_DIR}/src/Map/Map.cpp)

# Create Top Level Application File List
set(${PROJECT_NAME}_baseFiles
${TOP_LEVEL_ROOT_DIR}/src/MapReducer.cpp
${TOP_LEVEL_ROOT_DIR}/src/MapReducer.h
${TOP_LEVEL_ROOT_DIR}/src/main.cpp)

# Add source to this project's executable.

add_executable (${PROJECT_NAME} 
${${PROJECT_NAME}_baseFiles}
${FileIO_files}
${Sorter_files}
#${Reducer_files}
${Map_files}
)

target_include_directories(${PROJECT_NAME}
PRIVATE
${TOP_LEVEL_ROOT_DIR}/src/FileIO
${TOP_LEVEL_ROOT_DIR}/src/Sorter
#${TOP_LEVEL_ROOT_DIR}/src/ReduceClass
${TOP_LEVEL_ROOT_DIR}/src/Map
)

target_compile_definitions(${PROJECT_NAME}
PRIVATE 
-DPRINT_DEBUG)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)

#Test Bins
add_subdirectory(${TOP_LEVEL_ROOT_DIR}/src/FileIO)
add_subdirectory(${TOP_LEVEL_ROOT_DIR}/src/Sorter)
add_subdirectory(${TOP_LEVEL_ROOT_DIR}/src/Map)