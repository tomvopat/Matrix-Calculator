cmake_minimum_required(VERSION 3.10)
project(pa2_sem)

set(CMAKE_CXX_STANDARD 11)

add_executable(pa2_sem main.cpp matrix/CMatrix.cpp matrix/CMatrix.h tools/CPoint_2D.cpp tools/CPoint_2D.h matrix/CMatrixFull.cpp matrix/CMatrixFull.h matrix/CMatrixParse.cpp matrix/CMatrixParse.h matrix/vector/CVector.cpp matrix/vector/CVector.h matrix/vector/CVectorFull.cpp matrix/vector/CVectorFull.h matrix/vector/CVectorParse.cpp matrix/vector/CVectorParse.h tools/CInvalidMatrixException.cpp tools/CInvalidMatrixException.h)