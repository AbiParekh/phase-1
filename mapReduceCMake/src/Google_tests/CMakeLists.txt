########################################################################
# Note: CMake support is community-based. The maintainers do not use CMake
# internally.
#
# CMake build script for Google Test.
#
# To run the tests for Google Test itself on Linux, use 'make test' or
# ctest.  You can select which tests to run using 'ctest -R regex'.
# For more options, run 'ctest --help'.

# When other libraries are using a shared version of runtime libraries,
# Google Test also has to use one.

project(Google_tests)
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${SOURCE_DIR}/include ${SOURCE_DIR})

