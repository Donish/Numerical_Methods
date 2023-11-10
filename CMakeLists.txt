cmake_minimum_required(VERSION 3.22.1)
project(Chislaki)

set(CMAKE_CXX_STANDARD 17)

add_executable(Chislaki
        main.cpp
        matrix/matrix.cpp
        matrix/matrix.h
        Solution/Solution.h
        Solution/LUdecomposition.cpp
        Solution/LUdecomposition.h
)
