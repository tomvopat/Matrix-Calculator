cmake_minimum_required(VERSION 3.5)
project(pa2_sem)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Wall -Wextra -g")

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# The following folder will be included
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(
        pa2_sem
        matrix/CMatrix.cpp
        matrix/CMatrix.h
        matrix/CMatrixFull.cpp
        matrix/CMatrixFull.h
        matrix/CMatrixSparse.cpp
        matrix/CMatrixSparse.h
        tools/CPoint_2D.cpp
        tools/CPoint_2D.h
        tools/Numbers.cpp
        tools/Numbers.h
        tools/Consts.h
        tools/CInvalidMatrixException.cpp
        tools/CInvalidMatrixException.h
        tools/CMVCException.cpp
        tools/CMVCException.h
        ui/CModel.cpp
        ui/CModel.h
        ui/CView.cpp
        ui/CView.h
        ui/CController.cpp
        ui/CController.h Main.cpp
        tests/AllTests.h
        tests/Test1.h
        tests/Test2.h
        tests/Test3.h
        tests/Test4.h
        tests/Test5.h)