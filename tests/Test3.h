//
// Created by Tomáš Vopat on 02.05.18.
//

#ifndef PA2_SEM_TEST3_H
#define PA2_SEM_TEST3_H

#include <iostream>
#include "../matrix/CMatrixFull.h"

using namespace std;

//Testování násobení hustých a řídkých matic
void test3() {

    CMatrixFull f1(2, 3);
    CMatrixFull f2(3, 1);

    f1.setValue(1, CPoint_2D(0,0));
    f1.setValue(-5, CPoint_2D(1,0));
    f1.setValue(8, CPoint_2D(2,0));
    f1.setValue(3, CPoint_2D(0,1));
    f1.setValue(0, CPoint_2D(1,1));
    f1.setValue(-4, CPoint_2D(2,1));

    f2.setValue(0, CPoint_2D(0,0));
    f2.setValue(1, CPoint_2D(0,1));
    f2.setValue(2, CPoint_2D(0,2));

    CMatrix* mm = f1 * f2;
    assert(mm->getValue(CPoint_2D(0,0)) == 11);
    assert(mm->getValue(CPoint_2D(0,1)) == -8);

    mm->swapRows(0, 1);
    assert(mm->getValue(CPoint_2D(0,0)) == -8);
    assert(mm->getValue(CPoint_2D(0,1)) == 11);
    delete mm;

    CMatrixSparse s1(2, 3);
    CMatrixSparse s2(3, 1);

    s1.setValue(1, CPoint_2D(0,0));
    s1.setValue(-5, CPoint_2D(1,0));
    s1.setValue(8, CPoint_2D(2,0));
    s1.setValue(3, CPoint_2D(0,1));
    s1.setValue(0, CPoint_2D(1,1));
    s1.setValue(-4, CPoint_2D(2,1));

    s2.setValue(0, CPoint_2D(0,0));
    s2.setValue(1, CPoint_2D(0,1));
    s2.setValue(2, CPoint_2D(0,2));

    mm = s1 * s2;
    assert(mm->getValue(CPoint_2D(0,0)) == 11);
    assert(mm->getValue(CPoint_2D(0,1)) == -8);

    mm->swapRows(0, 1);
    assert(mm->getValue(CPoint_2D(0,0)) == -8);
    assert(mm->getValue(CPoint_2D(0,1)) == 11);
    delete mm;
}

#endif //PA2_SEM_TEST3_H
