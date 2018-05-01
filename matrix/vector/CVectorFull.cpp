//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CVectorFull.h"

CVectorFull::CVectorFull(int width): CVector(width), CMatrixFull(0, width) {

}

CVector *CVectorFull::operator+(const CVector &other) const {
    CVectorFull* newVector = new CVectorFull(m_width);
    for(int i = 0 ; i < m_width ; i++) {
        newVector->setValue(getValue(CPoint_2D(i,0)) + other.getValue(CPoint_2D(i,0)), CPoint_2D(i,0));
    }
    return newVector;
}

CVector *CVectorFull::operator-(const CVector &other) const {
    CVectorFull* newVector = new CVectorFull(m_width);
    for(int i = 0 ; i < m_width ; i++) {
        newVector->setValue(getValue(CPoint_2D(i,0)) - other.getValue(CPoint_2D(i,0)), CPoint_2D(i,0));
    }
    return newVector;
}

CVector *CVectorFull::operator*(int val) const {
    CVectorFull* newVector = new CVectorFull(m_width);
    for(int i = 0 ; i < m_width ; i++) {
        newVector->setValue(getValue(CPoint_2D(i,0)) * val, CPoint_2D(i,0));
    }
    return newVector;
}
