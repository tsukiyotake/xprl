cmake_minimum_required(VERSION 3.8)

project(test)

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)
if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

include_directories("../include")
add_executable(${PROJECT_NAME} test_simple.cpp)