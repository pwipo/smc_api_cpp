cmake_minimum_required(VERSION 3.12)
project(SMCApi)
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_library(SMCApi SHARED SMCApi.h SMCApi.cpp)

