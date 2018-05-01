//
// Created by Tomáš Vopat on 01.05.18.
//

#ifndef PA2_SEM_TEST2_H
#define PA2_SEM_TEST2_H

#include "../matrix/CMatrixSparse.h"

using namespace std;

void test2() {

    CMatrixSparse m1(0,0);
    try {
        m1.setValue(1, CPoint_2D(0,0));
        assert(false);
    } catch (CInvalidMatrixException ex) {}
    try {
        m1.setValue(1, CPoint_2D(-1,0));
        assert(false);
    } catch (CInvalidMatrixException ex) {}

    CMatrixSparse m2(2,3);
    int h, w;
    m2.getSize(h, w);
    assert((h == 2) && (w == 3));

    m2.setValue(5, CPoint_2D(0,0));
    assert(m2.getValue(CPoint_2D(0,0)) == 5);
    assert(m2.getNonZeroCount() == 1);
    m2.setValue(-4, CPoint_2D(1,0));
    assert(m2.getValue(CPoint_2D(1,0)) == -4);
    assert(m2.getNonZeroCount() == 2);
    m2.setValue(-100, CPoint_2D(2,0));
    assert(m2.getValue(CPoint_2D(2,0)) == -100);
    assert(m2.getNonZeroCount() == 3);

    m2.setValue(0, CPoint_2D(0,1));
    assert(m2.getValue(CPoint_2D(0,1)) == 0);
    assert(m2.getNonZeroCount() == 3);
    m2.setValue(17, CPoint_2D(1,1));
    assert(m2.getValue(CPoint_2D(1,1)) == 17);
    assert(m2.getNonZeroCount() == 4);
    m2.setValue(3, CPoint_2D(2,1));
    assert(m2.getValue(CPoint_2D(2,1)) == 3);
    assert(m2.getNonZeroCount() == 5);


    CMatrix *mm, *mmm;
    mm = m2.getTransposed();
    mm->getSize(h, w);
    assert((h == 3) && (w == 2));
    assert(mm->getNonZeroCount() == 5);
    assert(mm->getValue(CPoint_2D(0,0)) == 5);
    assert(mm->getValue(CPoint_2D(1,0)) == 0);
    assert(mm->getValue(CPoint_2D(0,1)) == -4);
    assert(mm->getValue(CPoint_2D(1,1)) == 17);
    assert(mm->getValue(CPoint_2D(0,2)) == -100);
    assert(mm->getValue(CPoint_2D(1,2)) == 3);

    mmm = mm->cut(CPoint_2D(1,1), CPoint_2D(1,2));
    delete mm;
    mm = mmm;

    mm->getSize(h, w);
    assert((h == 2) && (w == 1));
    assert(mm->getNonZeroCount() == 2);
    assert(mm->getValue(CPoint_2D(0,0)) == 17);
    assert(mm->getValue(CPoint_2D(0,1)) == 3);
    delete mm;

}

#endif //PA2_SEM_TEST2_H
