cmake_minimum_required(VERSION 3.0) 

set (PROJECT 
	quant_jumps)

set (BOOST_COMPONENTS 
	thread)
    
set (Boost_USE_STATIC_LIBS ON)
 
set (Boost_USE_MULTITHREADED ON)

set(SOURCES main.cpp
            calculator/calculator_base.cpp
            calculator/calculator_c.cpp)

set (HEADERS 
	calculator/calculator_base.h
    calculator/calculator_c.h
    complex.h)

set (EXECUTABLE_OUTPUT_PATH ../bin/debug)
set(MY_CXX_FLAGS  "-Wall -std=c++11")
set(CMAKE_CXX_FLAGS "-O3 ${MY_CXX_FLAGS}")



project (${PROJECT})

find_package(CUDA)
find_package(YamlCpp)
find_package (Threads)
find_package (Boost COMPONENTS ${BOOST_COMPONENTS} REQUIRED)

include_directories (calculator)
include_directories (./)

set(CUDA_NVCC_FLAGS ${CUDA_NVCC_FLAGS};-gencode arch=compute_20,code=sm_20)


CUDA_ADD_EXECUTABLE(${PROJECT} ${HEADERS} ${SOURCES})


target_link_libraries (${PROJECT} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})
