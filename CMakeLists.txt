cmake_minimum_required(VERSION 3.10)
project(pa2_sem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra")

add_executable(
        pa2_sem matrix/CMatrix.cpp
        matrix/CMatrix.h
        tools/CPoint_2D.cpp
        tools/CPoint_2D.h
        matrix/CMatrixFull.cpp
        matrix/CMatrixFull.h
        matrix/CMatrixSparse.cpp
        matrix/CMatrixSparse.h
        tools/CInvalidMatrixException.cpp
        tools/CInvalidMatrixException.h
        tools/Consts.h
        tests/Test.cpp
        tests/Test1.h
        tests/Test2.h
        tests/Test3.h tests/Test4.h tools/Numbers.cpp tools/Numbers.h tests/Test5.h)