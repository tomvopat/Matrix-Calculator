//
// Created by Tomáš Vopat on 03.05.18.
//

#ifndef PA2_SEM_TEST4_H
#define PA2_SEM_TEST4_H

#include "../matrix/CMatrixFull.h"
#include <iostream>

using namespace std;

//Testování GEMu
void test4() {
    CMatrixFull f1(4,5);
    f1.setValue(1, CPoint_2D(0,0));
    f1.setValue(2, CPoint_2D(1,0));
    f1.setValue(-3, CPoint_2D(2,0));
    f1.setValue(0, CPoint_2D(3,0));
    f1.setValue(1, CPoint_2D(4,0));

    f1.setValue(1, CPoint_2D(0,1));
    f1.setValue(-1, CPoint_2D(1,1));
    f1.setValue(0, CPoint_2D(2,1));
    f1.setValue(1, CPoint_2D(3,1));
    f1.setValue(-1, CPoint_2D(4,1));

    f1.setValue(0, CPoint_2D(0,2));
    f1.setValue(2, CPoint_2D(1,2));
    f1.setValue(-2, CPoint_2D(2,2));
    f1.setValue(0, CPoint_2D(3,2));
    f1.setValue(3, CPoint_2D(4,2));

    f1.setValue(2, CPoint_2D(0,3));
    f1.setValue(1, CPoint_2D(1,3));
    f1.setValue(1, CPoint_2D(2,3));
    f1.setValue(1, CPoint_2D(3,3));
    f1.setValue(0, CPoint_2D(4,3));
    assert(! f1.isInRowEchelonForm());

    CMatrix* mm = f1.gem();
    assert(mm->isInRowEchelonForm());
    assert(mm->getValue(CPoint_2D(0,0)) == 2);
    assert(mm->getValue(CPoint_2D(1,0)) == 1);
    assert(mm->getValue(CPoint_2D(2,0)) == 1);
    assert(mm->getValue(CPoint_2D(3,0)) == 1);
    assert(mm->getValue(CPoint_2D(4,0)) == 0);

    assert(mm->getValue(CPoint_2D(0,1)) == 0);
    assert(mm->getValue(CPoint_2D(1,1)) == 2);
    assert(mm->getValue(CPoint_2D(2,1)) == -2);
    assert(mm->getValue(CPoint_2D(3,1)) == 0);
    assert(mm->getValue(CPoint_2D(4,1)) == 3);

    assert(mm->getValue(CPoint_2D(0,2)) == 0);
    assert(mm->getValue(CPoint_2D(1,2)) == 0);
    assert(mm->getValue(CPoint_2D(2,2)) == -2);
    assert(mm->getValue(CPoint_2D(3,2)) == 0.5);
    assert(mm->getValue(CPoint_2D(4,2)) == 1.25);

    assert(mm->getValue(CPoint_2D(0,3)) == 0);
    assert(mm->getValue(CPoint_2D(1,3)) == 0);
    assert(mm->getValue(CPoint_2D(2,3)) == 0);
    assert(mm->getValue(CPoint_2D(3,3)) == -1);
    assert(mm->getValue(CPoint_2D(4,3)) == -2.5);
    assert(mm->getRank() == 4);
    delete mm;

    CMatrixFull f2(3,5);
    f2.setValue(1, CPoint_2D(0,0));
    f2.setValue(3, CPoint_2D(1,0));
    f2.setValue(-1, CPoint_2D(2,0));
    f2.setValue(4, CPoint_2D(3,0));
    f2.setValue(8, CPoint_2D(4,0));

    f2.setValue(1, CPoint_2D(0,1));
    f2.setValue(1, CPoint_2D(1,1));
    f2.setValue(-1, CPoint_2D(2,1));
    f2.setValue(-2, CPoint_2D(3,1));
    f2.setValue(2, CPoint_2D(4,1));

    f2.setValue(1, CPoint_2D(0,2));
    f2.setValue(7, CPoint_2D(1,2));
    f2.setValue(-1, CPoint_2D(2,2));
    f2.setValue(16, CPoint_2D(3,2));
    f2.setValue(20, CPoint_2D(4,2));

    assert(! f2.isInRowEchelonForm());

    CMatrix* mmm = f2.gem();
    assert(mmm->isInRowEchelonForm());
    assert(mmm->getValue(CPoint_2D(0,0)) == 1);
    assert(mmm->getValue(CPoint_2D(1,0)) == 3);
    assert(mmm->getValue(CPoint_2D(2,0)) == -1);
    assert(mmm->getValue(CPoint_2D(3,0)) == 4);
    assert(mmm->getValue(CPoint_2D(4,0)) == 8);

    assert(mmm->getValue(CPoint_2D(0,1)) == 0);
    assert(mmm->getValue(CPoint_2D(1,1)) == 4);
    assert(mmm->getValue(CPoint_2D(2,1)) == 0);
    assert(mmm->getValue(CPoint_2D(3,1)) == 12);
    assert(mmm->getValue(CPoint_2D(4,1)) == 12);

    assert(mmm->getValue(CPoint_2D(0,2)) == 0);
    assert(mmm->getValue(CPoint_2D(1,2)) == 0);
    assert(mmm->getValue(CPoint_2D(2,2)) == 0);
    assert(mmm->getValue(CPoint_2D(3,2)) == 0);
    assert(mmm->getValue(CPoint_2D(4,2)) == 0);
    assert(mmm->getRank() == 2);
    delete mmm;
}


#endif //PA2_SEM_TEST4_H
