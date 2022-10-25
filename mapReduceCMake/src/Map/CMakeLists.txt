# CMakeList.txt : CMake project for CMakeProject1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Map_Files")

# Create FileIO File List
set(FileIO_files 
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.cpp
${TOP_LEVEL_ROOT_DIR}/src/FileIO/FileIO.h)

# Add source to this project's executable.
add_executable (Map_Files "Map.cpp" "Map.h" "Test/TestMap.cpp" "Test/TestMap.h" ${FileIO_files})

target_include_directories(${PROJECT_NAME}
PRIVATE
${TOP_LEVEL_ROOT_DIR}/src/Map
${TOP_LEVEL_ROOT_DIR}/src/Map/Test
${TOP_LEVEL_ROOT_DIR}/src/FileIO
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Map_Files PROPERTY CXX_STANDARD 17)
endif()

# TODO: Add tests and install targets if needed.
