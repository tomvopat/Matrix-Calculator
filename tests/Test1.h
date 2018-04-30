//
// Created by Tomáš Vopat on 30.04.18.
//

#include <iostream>
#include "../matrix/CMatrixFull.h"
#include "../tools/CInvalidMatrixException.h"

void test1() {

    CMatrixFull m1(0, 0);
    std::cout << m1;

    try{
        CMatrixFull m2(0, 10);
        assert(false);
    } catch(CInvalidMatrixException ex) {
        std::cout << ex << std::endl;
    }

    try{
        CMatrixFull m3(10, 0);
        assert(false);
    } catch(CInvalidMatrixException ex) {
        std::cout << ex << std::endl;
    }

    CMatrixFull m4(1, 1);
    std::cout << m4;

    CMatrixFull m5(2, 1);
    std::cout << m5;

    CMatrixFull m6(1, 2);
    std::cout << m6;

    CMatrixFull m7(10, 10);
    m7.setValue(1, CPoint_2D(0,0));
    m7.setValue(1, CPoint_2D(1,0));
    m7.setValue(1, CPoint_2D(0,1));
    try {
        m7.setValue(1, CPoint_2D(-1,0));
        assert(false);
    } catch(CInvalidMatrixException ex) {
        std::cout << ex << std::endl;
    }
    try{
        m7.setValue(1, CPoint_2D(0,-1));
        assert(false);
    } catch(CInvalidMatrixException ex) {
        std::cout << ex << std::endl;
    }
    try {
        m7.setValue(1, CPoint_2D(9,10));
        assert(false);
    } catch(CInvalidMatrixException ex) {
        std::cout << ex << std::endl;
    }
    m7.setValue(1, CPoint_2D(9,9));
    m7.setValue(1, CPoint_2D(8,9));
    m7.setValue(1, CPoint_2D(9,8));

    m7.setValue(1, CPoint_2D(9,0));
    m7.setValue(1, CPoint_2D(8,0));
    m7.setValue(1, CPoint_2D(9,1));

    m7.setValue(1, CPoint_2D(0,9));
    m7.setValue(1, CPoint_2D(0,8));
    m7.setValue(1, CPoint_2D(1,9));
    std::cout << m7;

    int h, w;
    m7.getSize(h, w);
    assert((h == 10) && (w == 10));
    assert(m7.getValue(CPoint_2D(0, 0)) == 1);
    assert(m7.getValue(CPoint_2D(1, 0)) == 1);
    assert(m7.getValue(CPoint_2D(0, 1)) == 1);
    assert(m7.getValue(CPoint_2D(2, 0)) == 0);
    assert(m7.getValue(CPoint_2D(0, 2)) == 0);
    assert(m7.getValue(CPoint_2D(1, 1)) == 0);
    assert(m7.getValue(CPoint_2D(9, 9)) == 1);
    assert(m7.getValue(CPoint_2D(8, 9)) == 1);
    assert(m7.getValue(CPoint_2D(9, 8)) == 1);
    assert(m7.getValue(CPoint_2D(8, 8)) == 0);

    CMatrix* m8;
}