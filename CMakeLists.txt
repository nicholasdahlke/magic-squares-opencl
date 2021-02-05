cmake_minimum_required(VERSION 3.17)
project(squares)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCL REQUIRED)
find_package( Threads )
add_executable(squares main.cpp)
target_link_libraries( squares ${CMAKE_THREAD_LIBS_INIT} )
target_link_libraries( squares OpenCL::OpenCL)