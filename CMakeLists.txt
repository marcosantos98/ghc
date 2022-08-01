cmake_minimum_required(VERSION 3.20)

project(ghc CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -pedantic")

add_executable(ghc main.cpp)

install(TARGETS ghc DESTINATION bin)

target_include_directories(ghc PUBLIC "./vendor/")