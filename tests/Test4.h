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
    cout << f1 << endl;

    CMatrix* mm = f1.gem();
    assert(mm->isInRowEchelonForm());
    cout << *mm << endl;
}


#endif //PA2_SEM_TEST4_H
