cmake_minimum_required(VERSION 3.13)
project(Lasd_es1)
set(CMAKE_CXX_STANDARD 14)
# +++++++ Exercise 1 +++++++
#include_directories(exercise1/container exercise1/list exercise1/vector exercise1/zlasdtest exercise1/zmytest)
#add_executable(main
#        exercise1/zlasdtest/exercise1/fulltest.cpp
#        exercise1/zlasdtest/exercise1/simpletest.cpp
#        exercise1/zlasdtest/container/container.cpp
#        exercise1/zlasdtest/test.cpp
#        exercise1/zmytest/test.cpp
#        exercise1/main.cpp)

# +++++++ Exercise 2 +++++++
include_directories(exercise2/container exercise2/list exercise2/vector exercise2/zlasdtest exercise2/zmytest exercise2/stack/vec)
add_executable(main
        exercise2/zlasdtest/exercise2/fulltest.cpp
        exercise1/zlasdtest/exercise1/simpletest.cpp
        exercise1/zlasdtest/exercise1/fulltest.cpp
        exercise2/zlasdtest/exercise2/simpletest.cpp
        exercise2/zlasdtest/container/container.cpp
        exercise2/zlasdtest/test.cpp
        exercise2/zmytest/test.cpp
        exercise2/main.cpp)