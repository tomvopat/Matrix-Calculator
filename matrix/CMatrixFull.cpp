//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrixFull.h"
#include "../tools/CInvalidMatrixException.h"
#include "../tools/Numbers.h"

CMatrixFull::CMatrixFull(int height, int width): CMatrix(height, width) {
    m_data.resize(height);
    for(std::vector<double>& item : m_data) {
        item.resize(width);
    }
}

CMatrix* CMatrixFull::duplicate() const {
    return new CMatrixFull(*this);
}

CMatrix* CMatrixFull::operator + (const CMatrix& other) const {

    if((m_width != other.getWidth()) || (m_height != other.getHeight())) throw CInvalidMatrixException("Nelze sčítat matice různých rozměrů.");
    CMatrixFull* newMatrix = new CMatrixFull(m_height, m_width);
    CMatrix::addition(*this, other, *newMatrix);
    return newMatrix;
}

CMatrix* CMatrixFull::operator - (const CMatrix& other) const {
    if((m_width != other.getWidth()) || (m_height != other.getHeight())) throw CInvalidMatrixException("Nelze odčítat matice různých rozměrů.");
    CMatrixFull* newMatrix = new CMatrixFull(m_height, m_width);
    CMatrix::subtraction(*this, other, *newMatrix);
    return newMatrix;
}

CMatrix* CMatrixFull::operator * (const CMatrix& other) const {
    if(m_width != other.getHeight()) throw CInvalidMatrixException("Tyto matice nelze násobit");
    CMatrixFull* newMatrix = new CMatrixFull(m_height, other.getWidth());
    CMatrix::multiplication(*this, other, *newMatrix);
    return newMatrix;
}

void CMatrixFull::swapRows(int i, int j) {
    if((i >= m_height) || (j >= m_height)) throw CInvalidMatrixException("Neplatný řádkový index.");

    std::vector<double> tmp(m_data[i]);
    m_data[i] = m_data[j];
    m_data[j] = tmp;
}

double CMatrixFull::getValue(const CPoint_2D& point) const {
    if(! isValid(point)) throw CInvalidMatrixException("Neplatný bod v matici.");

    return m_data[point.getY()][point.getX()];

}

void CMatrixFull::setValue(double value, const CPoint_2D& point) {
    if(! isValid(point)) throw CInvalidMatrixException("Neplatný bod v matici.");

    //Zvýšení počtu nenulových prvků
    if(Numbers::isNull(m_data[point.getY()][point.getX()]) && !Numbers::isNull(value)) m_nonZeroCount++;

    //Snížení počtu nenulových prvků
    if(!Numbers::isNull(m_data[point.getY()][point.getX()]) && Numbers::isNull(value)) m_nonZeroCount--;

    m_data[point.getY()][point.getX()] = value;
}

CMatrix* CMatrixFull::getTransposed() const {
    CMatrixFull* newMatrix = new CMatrixFull(m_width, m_height);
    for(int h = 0 ; h < m_height ; h++) {
        for(int w = 0 ; w < m_width ; w++) {
            newMatrix->setValue(getValue(CPoint_2D(w, h)), CPoint_2D(h, w));
        }
    }
    return newMatrix;
}

CMatrix* CMatrixFull::cut(const CPoint_2D &leftTop, const CPoint_2D &rightBottom) const {
    if(!isValid(leftTop) || !isValid(rightBottom)) throw CInvalidMatrixException("Neplatné indexy výřezu.");
    if(! (leftTop <= rightBottom)) throw CInvalidMatrixException("Neplatné body pro výřez.");

    CMatrixFull* newMatrix = new CMatrixFull(rightBottom.getY() - leftTop.getY() + 1, rightBottom.getX() - leftTop.getX() + 1);
    for(int h = 0 ; h < newMatrix->m_height ; h++) {
        for(int w = 0 ; w < newMatrix->m_width ; w++) {
            newMatrix->setValue(getValue(CPoint_2D(w + leftTop.getX(), h + leftTop.getY())), CPoint_2D(w, h));
        }
    }
    return newMatrix;
}

bool CMatrixFull::isZeroRow(int i) const {
    if(i >= m_height) throw CInvalidMatrixException("Neplatný řádek matice.");

    for(int j = 0 ; j < m_width ; j++) {
        if(! Numbers::isNull(getValue(CPoint_2D(j, i)))) return false;
    }
    return true;
}

CMatrix* CMatrixFull::newMatrix(int height, int width) const {
    return new CMatrixFull(height, width);
}