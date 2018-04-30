//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrixFull.h"
#include "../tools/CInvalidMatrixException.h"

#include <iomanip>

CMatrixFull::CMatrixFull(int height, int width): CMatrix(height, width) {
    m_data.resize(height);
    for(std::vector<double>& item : m_data) {
        item.resize(width);
    }
}

std::ostream& CMatrixFull::print(std::ostream& os) const {
    for(int h = 0 ; h < m_height ; h++) {
        for(int w = 0 ; w < m_width ; w++) {
            os << getValue(CPoint_2D(w, h)) << std::setprecision(3) << std::setw(3) << " ";
        }
        os << "\n";
    }
    return os;
}

CMatrix* CMatrixFull::operator*(const CMatrix &other) const {
    return new CMatrixFull(0,0);
}

double CMatrixFull::getValue(const CPoint_2D& point) const {
    if(! isValid(point)) throw CInvalidMatrixException("Neplatný bod v matici.");

    return m_data[point.getY()][point.getX()];

}

void CMatrixFull::setValue(double value, const CPoint_2D& point) {
    if(! isValid(point)) throw CInvalidMatrixException("Neplatný bod v matici.");

    //Zvýšení počtu nenulových prvků
    if((m_data[point.getY()][point.getX()] == 0) && (value != 0)) m_nonZeroCount++;

    //Snížení počtu nenulových prvků
    if((m_data[point.getY()][point.getX()] != 0) && (value == 0)) m_nonZeroCount--;

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

bool CMatrixFull::isRegular() const {
    return false;
}

int CMatrixFull::getRank() const {
    return 0;
}

int CMatrixFull::getDeterminant() const {
    return 0;
}
