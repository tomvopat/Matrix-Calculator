//
// Created by Tomáš Vopat on 30.04.18.
//

#include <iostream>
#include "../matrix/CMatrixFull.h"
#include "../tools/CInvalidMatrixException.h"

using namespace std;

//Testy pro plnou matici
void test1() {

    CMatrixFull m1(0, 0);
    std::cout << m1;

    try{
        CMatrixFull m2(0, 1);
        assert(false);
    } catch(CInvalidMatrixException ex) {}
    try{
        CMatrixFull m3(1, 0);
        assert(false);
    } catch(CInvalidMatrixException ex) {}

    CMatrixFull m8(2, 2);
    int h, w;
    m8.getSize(h, w);
    assert((h == 2) && (w == 2));
    assert(m8.getNonZeroCount() == 0);
    try {
        m8.setValue(-100, CPoint_2D(-1,0));
        assert(false);
    } catch(CInvalidMatrixException ex) {}
    try{
        m8.setValue(-100, CPoint_2D(0,-1));
        assert(false);
    } catch(CInvalidMatrixException ex) {}
    try {
        m8.setValue(-100, CPoint_2D(2,2));
        assert(false);
    } catch(CInvalidMatrixException ex) {}

    m8.setValue(8, CPoint_2D(0,0));
    assert(m8.getNonZeroCount() == 1);
    m8.setValue(-4, CPoint_2D(1,0));
    assert(m8.getNonZeroCount() == 2);
    m8.setValue(6, CPoint_2D(0,1));
    assert(m8.getNonZeroCount() == 3);
    m8.setValue(21, CPoint_2D(1,1));
    assert(m8.getNonZeroCount() == 4);
    assert(m8.getValue(CPoint_2D(0,0)) == 8);
    assert(m8.getValue(CPoint_2D(1,0)) == -4);
    assert(m8.getValue(CPoint_2D(0,1)) == 6);
    assert(m8.getValue(CPoint_2D(1,1)) == 21);

    CMatrixFull m9(2,2);
    assert(m9.getNonZeroCount() == 0);
    m9.setValue(10, CPoint_2D(0,0));
    assert(m9.getNonZeroCount() == 1);
    m9.setValue(-5, CPoint_2D(1,0));
    assert(m9.getNonZeroCount() == 2);
    m9.setValue(12, CPoint_2D(0,1));
    assert(m9.getNonZeroCount() == 3);
    m9.setValue(7, CPoint_2D(1,1));
    assert(m9.getNonZeroCount() == 4);
    assert(m9.getValue(CPoint_2D(0,0)) == 10);
    assert(m9.getValue(CPoint_2D(1,0)) == -5);
    assert(m9.getValue(CPoint_2D(0,1)) == 12);
    assert(m9.getValue(CPoint_2D(1,1)) == 7);

    CMatrix* mm = m8 + m9;
    assert(mm->getNonZeroCount() == 4);
    assert(mm->getValue(CPoint_2D(0,0)) == 18);
    assert(mm->getValue(CPoint_2D(1,0)) == -9);
    assert(mm->getValue(CPoint_2D(0,1)) == 18);
    assert(mm->getValue(CPoint_2D(1,1)) == 28);
    delete mm;

    mm = m8 - m9;
    assert(mm->getNonZeroCount() == 4);
    assert(mm->getValue(CPoint_2D(0,0)) == -2);
    assert(mm->getValue(CPoint_2D(1,0)) == 1);
    assert(mm->getValue(CPoint_2D(0,1)) == -6);
    assert(mm->getValue(CPoint_2D(1,1)) == 14);

    mm->setValue(0, CPoint_2D(0,0));
    assert(mm->getNonZeroCount() == 3);
    mm->setValue(0, CPoint_2D(1,0));
    assert(mm->getNonZeroCount() == 2);
    mm->setValue(0, CPoint_2D(0,1));
    assert(mm->getNonZeroCount() == 1);
    mm->setValue(0, CPoint_2D(1,1));
    assert(mm->getNonZeroCount() == 0);
    mm->setValue(1, CPoint_2D(0,0));
    assert(mm->getNonZeroCount() == 1);
    delete mm;

    mm = m8.merge(m9, true);
    mm->getSize(h, w);
    assert((h == 2) && (w == 4));
    assert(mm->getValue(CPoint_2D(0,0)) == 8);
    assert(mm->getValue(CPoint_2D(1,0)) == -4);
    assert(mm->getValue(CPoint_2D(2,0)) == 10);
    assert(mm->getValue(CPoint_2D(3,0)) == -5);
    assert(mm->getValue(CPoint_2D(0,1)) == 6);
    assert(mm->getValue(CPoint_2D(1,1)) == 21);
    assert(mm->getValue(CPoint_2D(2,1)) == 12);
    assert(mm->getValue(CPoint_2D(3,1)) == 7);
    delete mm;

    mm = m8.merge(m9, false);
    mm->getSize(h, w);
    assert((h == 4) && (w == 2));
    assert(mm->getValue(CPoint_2D(0,0)) == 8);
    assert(mm->getValue(CPoint_2D(1,0)) == -4);
    assert(mm->getValue(CPoint_2D(0,1)) == 6);
    assert(mm->getValue(CPoint_2D(1,1)) == 21);
    assert(mm->getValue(CPoint_2D(0,2)) == 10);
    assert(mm->getValue(CPoint_2D(1,2)) == -5);
    assert(mm->getValue(CPoint_2D(0,3)) == 12);
    assert(mm->getValue(CPoint_2D(1,3)) == 7);

    CMatrix* mmm = mm->getTransposed();
    delete mm;
    mm = mmm;
    mm->getSize(h, w);
    assert((h == 2) && (w == 4));
    assert(mm->getValue(CPoint_2D(0,0)) == 8);
    assert(mm->getValue(CPoint_2D(1,0)) == 6);
    assert(mm->getValue(CPoint_2D(2,0)) == 10);
    assert(mm->getValue(CPoint_2D(3,0)) == 12);
    assert(mm->getValue(CPoint_2D(0,1)) == -4);
    assert(mm->getValue(CPoint_2D(1,1)) == 21);
    assert(mm->getValue(CPoint_2D(2,1)) == -5);
    assert(mm->getValue(CPoint_2D(3,1)) == 7);

    try {
        mmm = mm->cut(CPoint_2D(1,1), CPoint_2D(0,1));
    } catch(CInvalidMatrixException ex) {}

    mmm = mm->cut(CPoint_2D(0,0), CPoint_2D(0,0));
    mmm->getSize(h, w);
    assert((h == 1) && (w == 1));
    assert(mmm->getValue(CPoint_2D(0,0)) == 8);
    delete mmm;

    mmm = mm->cut(CPoint_2D(1,0), CPoint_2D(3,1));
    delete mm;
    mm = mmm;
    mm->getSize(h, w);
    assert((h == 2) && (w == 3));
    assert(mm->getValue(CPoint_2D(0,0)) == 6);
    assert(mm->getValue(CPoint_2D(1,0)) == 10);
    assert(mm->getValue(CPoint_2D(2,0)) == 12);
    assert(mm->getValue(CPoint_2D(0,1)) == 21);
    assert(mm->getValue(CPoint_2D(1,1)) == -5);
    assert(mm->getValue(CPoint_2D(2,1)) == 7);
    delete mm;
}