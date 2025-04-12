cmake_minimum_required(VERSION 3.10.0)
project(task_32.6.1 VERSION 0.1.0 LANGUAGES C CXX)

add_executable(task_32.6.1 ClassThatUsesDB.cpp ClassThatUsesDBTest.cpp main.cpp)

include(CTest)
enable_testing()

