cmake_minimum_required(VERSION "3.25.0")


#specify project
project("phase-1")

"$(phase-1)"

#source for project executable 
add_executable(ReduceClass "Reduce.cpp" "Reduce.h")

install(TARGET ReduceClass DESTINATION "ReduceClass/bin")
install(FILES "Reduce.cpp" "Reduce.h" DESTINATION src)
