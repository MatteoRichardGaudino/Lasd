cmake_minimum_required(VERSION 3.13)
project(Lasd)
set(CMAKE_CXX_STANDARD 14)

include_directories(
        exercise4/container
        exercise4/list
        exercise4/vector
        exercise4/zlasdtest
        exercise4/zmytest
        exercise4/stack/vec
        exercise4/binarytree/vec
        exercise4/binarytree/lnk
        exercise4/iterator
        exercise4/bst)
add_executable(main
        exercise5/zlasdtest/container/container.cpp
#        exercise5/zmytest/test.cpp
        exercise5/zlasdtest/test.cpp
        exercise5/main.cpp

        exercise1/zlasdtest/exercise1/simpletest.cpp
        exercise1/zlasdtest/exercise1/fulltest.cpp

        exercise2/zlasdtest/exercise2/simpletest.cpp
        exercise2/zlasdtest/exercise2/fulltest.cpp

        exercise3/zlasdtest/exercise3/simpletest.cpp
        exercise3/zlasdtest/exercise3/fulltest.cpp

        exercise4/zlasdtest/exercise4/simpletest.cpp
        exercise4/zlasdtest/exercise4/fulltest.cpp

        exercise5/zlasdtest/exercise5/simpletest.cpp
        exercise5/zlasdtest/exercise5/fulltest.cpp
        )