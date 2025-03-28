cmake_minimum_required(VERSION 3.10)
project(TDOA_Localization)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(TDOA_Localization src/main.cpp)

