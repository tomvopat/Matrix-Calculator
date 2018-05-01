//
// Created by Tomáš Vopat on 01.05.18.
//

#ifndef PA2_SEM_TEST2_H
#define PA2_SEM_TEST2_H

#include "../matrix/CMatrixSparse.h"

using namespace std;

void test2() {

    CMatrixSparse m1(0,0);
    cout << m1;
    cout << "---------------\n";
    try {
        m1.setValue(1, CPoint_2D(0,0));
        assert(false);
    } catch (CInvalidMatrixException ex) {}
    try {
        m1.setValue(1, CPoint_2D(-1,0));
        assert(false);
    } catch (CInvalidMatrixException ex) {}

    CMatrixSparse m2(2,2);
    m2.setValue(5, CPoint_2D(0,0));
    assert(m2.getValue(CPoint_2D(0,0)) == 5);
    assert(m2.getNonZeroCount() == 1);
    m2.setValue(-4, CPoint_2D(1,0));
    assert(m2.getValue(CPoint_2D(1,0)) == -4);
    assert(m2.getNonZeroCount() == 2);
    m2.setValue(0, CPoint_2D(0,1));
    assert(m2.getValue(CPoint_2D(0,1)) == 0);
    assert(m2.getNonZeroCount() == 2);
    m2.setValue(17, CPoint_2D(1,1));
    assert(m2.getValue(CPoint_2D(1,1)) == 17);
    assert(m2.getNonZeroCount() == 3);
    cout << m2;
    cout << "---------------\n";


}

#endif //PA2_SEM_TEST2_H
