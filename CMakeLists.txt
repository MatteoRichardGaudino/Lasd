cmake_minimum_required(VERSION 3.13)
project(Lasd_es1)
set(CMAKE_CXX_STANDARD 14)
include_directories(exercise1/container exercise1/list exercise1/vector exercise1/zlasdtest)
add_executable(main
        exercise1/zlasdtest/exercise1/fulltest.cpp
        exercise1/zlasdtest/container/container.cpp
        exercise1/zlasdtest/test.cpp
        exercise1/zmytest/test.cpp
        exercise1/main.cpp)