//
// Created by Tomáš Vopat on 03.05.18.
//

#ifndef PA2_SEM_TEST4_H
#define PA2_SEM_TEST4_H

#include "../matrix/CMatrixFull.h"
#include <iostream>

using namespace std;

//Testování GEMu, horního stupňovitého tvaru, výpočtu hodnosti, vyhodnocení zda je matice regulární, výpočet determinantu
void test4() {
    CMatrixFull f1(4,4);
    f1.setValue(1, CPoint_2D(0,0));
    f1.setValue(2, CPoint_2D(1,0));
    f1.setValue(-3, CPoint_2D(2,0));
    f1.setValue(0, CPoint_2D(3,0));

    f1.setValue(1, CPoint_2D(0,1));
    f1.setValue(-1, CPoint_2D(1,1));
    f1.setValue(0, CPoint_2D(2,1));
    f1.setValue(1, CPoint_2D(3,1));

    f1.setValue(0, CPoint_2D(0,2));
    f1.setValue(2, CPoint_2D(1,2));
    f1.setValue(-2, CPoint_2D(2,2));
    f1.setValue(0, CPoint_2D(3,2));

    f1.setValue(2, CPoint_2D(0,3));
    f1.setValue(1, CPoint_2D(1,3));
    f1.setValue(1, CPoint_2D(2,3));
    f1.setValue(1, CPoint_2D(3,3));
    assert(! f1.isInRowEchelonForm());

    CMatrix* mm = f1.gem();
    assert(mm->isInRowEchelonForm());
    assert(mm->getValue(CPoint_2D(0,0)) == 2);
    assert(mm->getValue(CPoint_2D(1,0)) == 1);
    assert(mm->getValue(CPoint_2D(2,0)) == 1);
    assert(mm->getValue(CPoint_2D(3,0)) == 1);

    assert(mm->getValue(CPoint_2D(0,1)) == 0);
    assert(mm->getValue(CPoint_2D(1,1)) == 2);
    assert(mm->getValue(CPoint_2D(2,1)) == -2);
    assert(mm->getValue(CPoint_2D(3,1)) == 0);

    assert(mm->getValue(CPoint_2D(0,2)) == 0);
    assert(mm->getValue(CPoint_2D(1,2)) == 0);
    assert(mm->getValue(CPoint_2D(2,2)) == -2);
    assert(mm->getValue(CPoint_2D(3,2)) == 0.5);

    assert(mm->getValue(CPoint_2D(0,3)) == 0);
    assert(mm->getValue(CPoint_2D(1,3)) == 0);
    assert(mm->getValue(CPoint_2D(2,3)) == 0);
    assert(mm->getValue(CPoint_2D(3,3)) == -1);
    assert(mm->getRank() == 4);
    assert(mm->isRegular());
    assert(mm->getDeterminant() == 8);
    delete mm;

    CMatrixFull f2(3,4);
    f2.setValue(1, CPoint_2D(0,0));
    f2.setValue(3, CPoint_2D(1,0));
    f2.setValue(-1, CPoint_2D(2,0));
    f2.setValue(4, CPoint_2D(3,0));

    f2.setValue(1, CPoint_2D(0,1));
    f2.setValue(1, CPoint_2D(1,1));
    f2.setValue(-1, CPoint_2D(2,1));
    f2.setValue(-2, CPoint_2D(3,1));

    f2.setValue(1, CPoint_2D(0,2));
    f2.setValue(7, CPoint_2D(1,2));
    f2.setValue(-1, CPoint_2D(2,2));
    f2.setValue(16, CPoint_2D(3,2));

    assert(! f2.isInRowEchelonForm());

    CMatrix* mmm = f2.gem();
    assert(mmm->isInRowEchelonForm());
    assert(mmm->getValue(CPoint_2D(0,0)) == 1);
    assert(mmm->getValue(CPoint_2D(1,0)) == 3);
    assert(mmm->getValue(CPoint_2D(2,0)) == -1);
    assert(mmm->getValue(CPoint_2D(3,0)) == 4);

    assert(mmm->getValue(CPoint_2D(0,1)) == 0);
    assert(mmm->getValue(CPoint_2D(1,1)) == 4);
    assert(mmm->getValue(CPoint_2D(2,1)) == 0);
    assert(mmm->getValue(CPoint_2D(3,1)) == 12);

    assert(mmm->getValue(CPoint_2D(0,2)) == 0);
    assert(mmm->getValue(CPoint_2D(1,2)) == 0);
    assert(mmm->getValue(CPoint_2D(2,2)) == 0);
    assert(mmm->getValue(CPoint_2D(3,2)) == 0);
    assert(mmm->getRank() == 2);
    assert(! mmm->isRegular());
    delete mmm;

    CMatrixSparse s1(3,3);
    s1.setValue(0, CPoint_2D(0,0));
    s1.setValue(2, CPoint_2D(1,0));
    s1.setValue(1, CPoint_2D(2,0));

    s1.setValue(0, CPoint_2D(0,1));
    s1.setValue(1, CPoint_2D(1,1));
    s1.setValue(2, CPoint_2D(2,1));

    s1.setValue(0, CPoint_2D(0,2));
    s1.setValue(0, CPoint_2D(1,2));
    s1.setValue(0, CPoint_2D(2,2));
    assert(s1.getRank() == 2);
    assert(s1.isRegular());
    assert(s1.getDeterminant() == 0);

    mm = s1.cut(CPoint_2D(1,0), CPoint_2D(2,1));
    assert(mm->getDeterminant() == 3);
    delete mm;
}


#endif //PA2_SEM_TEST4_H
