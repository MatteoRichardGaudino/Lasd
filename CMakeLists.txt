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
#include_directories(exercise2/container exercise2/list exercise2/vector exercise2/zlasdtest exercise2/zmytest exercise2/stack/vec)
#add_executable(main
#        exercise2/zlasdtest/exercise2/fulltest.cpp
#        exercise1/zlasdtest/exercise1/simpletest.cpp
#        exercise1/zlasdtest/exercise1/fulltest.cpp
#        exercise2/zlasdtest/exercise2/simpletest.cpp
#        exercise2/zlasdtest/container/container.cpp
#        exercise2/zlasdtest/test.cpp
#        exercise2/zmytest/test.cpp
#        exercise2/main.cpp)
# +++++++ Exercise 3 +++++++
include_directories(exercise3/container exercise3/list exercise3/vector exercise3/zlasdtest exercise3/zmytest exercise3/stack/vec
        exercise3/binarytree/vec
        exercise3/binarytree/lnk
        exercise3/iterator)
add_executable(main
        exercise3/zlasdtest/container/container.cpp
        exercise3/zmytest/test.cpp
        exercise1/zlasdtest/exercise1/simpletest.cpp
        exercise1/zlasdtest/exercise1/fulltest.cpp
        exercise2/zlasdtest/exercise2/simpletest.cpp
        exercise2/zlasdtest/exercise2/fulltest.cpp
        exercise3/zlasdtest/exercise3/simpletest.cpp
        exercise3/zlasdtest/exercise3/fulltest.cpp
        exercise3/zlasdtest/test.cpp
        exercise3/main.cpp)