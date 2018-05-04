//
// Created by Tomáš Vopat on 04.05.18.
//

#ifndef PA2_SEM_TEST5_H
#define PA2_SEM_TEST5_H

#include "../matrix/CMatrixSparse.h"

using namespace std;

//výpočet inverzní matice
void test5() {

    CMatrixSparse s1(3,3);
    s1.setValue(1, CPoint_2D(0,0));
    s1.setValue(2, CPoint_2D(1,0));
    s1.setValue(0, CPoint_2D(2,0));

    s1.setValue(-1, CPoint_2D(0,1));
    s1.setValue(1, CPoint_2D(1,1));
    s1.setValue(1, CPoint_2D(2,1));

    s1.setValue(1, CPoint_2D(0,2));
    s1.setValue(2, CPoint_2D(1,2));
    s1.setValue(3, CPoint_2D(2,2));
    cout << s1 << endl;

    CMatrix* mm = s1.cofactor();
    cout << *mm << endl;
    assert(mm->getValue(CPoint_2D(0,0)) == 1);
    assert(mm->getValue(CPoint_2D(1,0)) == 4);
    assert(mm->getValue(CPoint_2D(2,0)) == -3);

    assert(mm->getValue(CPoint_2D(0,1)) == -6);
    assert(mm->getValue(CPoint_2D(1,1)) == 3);
    assert(mm->getValue(CPoint_2D(2,1)) == 0);

    assert(mm->getValue(CPoint_2D(0,2)) == 2);
    assert(mm->getValue(CPoint_2D(1,2)) == -1);
    assert(mm->getValue(CPoint_2D(2,2)) == 3);
    delete mm;



}

#endif //PA2_SEM_TEST5_H
