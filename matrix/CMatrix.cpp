//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrix.h"
#include "../tools/CInvalidMatrixException.h"
#include "CMatrixFull.h"

#include <iomanip>

CMatrix::CMatrix(int height, int width): m_nonZeroCount(0) {
    //Pokud je výška/šířka nulová, pak musí být nulový i druhý parametr.
    if(((height == 0) || (width == 0)) && ((height != 0) || (width != 0))) {
        throw CInvalidMatrixException("Neplatná velikost matice.");
    }

    //Velikost nesmí být záporná
    if((height < 0) || (width < 0)) {
        throw CInvalidMatrixException("Záporná velikost matice.");
    }

    m_height = height;
    m_width = width;
}

CMatrix* CMatrix::operator + (const CMatrix& other) const {
    if((m_height != other.m_height) || (m_width != other.m_width)) {
        throw CInvalidMatrixException("Nelze sčítat matice různých rozměrů.");
    }

    CMatrixFull* newMatrix = new CMatrixFull(m_height, m_width);
    for(int h = 0 ; h < m_height ; h++) {
        for(int w = 0 ; w < m_width ; w++) {
            newMatrix->setValue(getValue(CPoint_2D(w, h)) + other.getValue(CPoint_2D(w, h)), CPoint_2D(w, h));
        }
    }
    return newMatrix;
}

CMatrix* CMatrix::operator - (const CMatrix& other) const {
    if((m_height != other.m_height) || (m_width != other.m_width)) {
        throw CInvalidMatrixException("Nelze odečítat matice různých rozměrů.");
    }

    CMatrixFull* newMatrix = new CMatrixFull(m_height, m_width);
    for(int h = 0 ; h < m_height ; h++) {
        for(int w = 0 ; w < m_width ; w++) {
            newMatrix->setValue(getValue(CPoint_2D(w, h)) - other.getValue(CPoint_2D(w, h)), CPoint_2D(w, h));
        }
    }
    return newMatrix;
}

std::ostream& operator << (std::ostream& os, const CMatrix& matrix) {
    matrix.print(os);
    return os;
}

std::ostream& CMatrix::print(std::ostream& os) const {
    for(int h = 0 ; h < m_height ; h++) {
        for(int w = 0 ; w < m_width ; w++) {
            os << getValue(CPoint_2D(w, h)) << std::setprecision(3) << std::setw(3) << " ";
        }
        os << "\n";
    }
    return os;
}

void CMatrix::getSize(int& height, int& width) const {
    height = m_height;
    width = m_width;
}

int CMatrix::getNonZeroCount() const {
   return m_nonZeroCount;
}

bool CMatrix::isValid(const CPoint_2D& point) const {
    if((point.getX() < 0) || (point.getX() >= m_width)) {
        return false;
    }

    if((point.getY() < 0) || (point.getY() >= m_height)) {
        return false;
    }

    return true;
}

CMatrix* CMatrix::merge(const CMatrix& other, bool horizontally) const {
    //Horizontální merge
    if(horizontally) {
        if(m_height != other.m_height) throw CInvalidMatrixException("Nelze horizontálně mergovat matice s různým počtem řádků.");
        CMatrixFull* newMatrix = new CMatrixFull(m_height, m_width + other.m_width);
        for(int h = 0 ; h < m_height ; h++) {
            for(int w = 0 ; w < m_width + other.m_width ; w++) {
                //První matice
                if(w < m_width) {
                    newMatrix->setValue(getValue(CPoint_2D(w, h)), CPoint_2D(w, h));
                }
                    //Druhá matice
                else {
                    newMatrix->setValue(other.getValue(CPoint_2D(w - m_width, h)), CPoint_2D(w, h));
                }
            }
        }
        return newMatrix;
    }
        //Vertikální merge
    else {
        if(m_width != other.m_width) throw CInvalidMatrixException("Nelze vertikálně mergovat matice s různým počtem sloupců.");
        CMatrixFull* newMatrix = new CMatrixFull(m_height + other.m_height, m_width);
        for(int h = 0 ; h < m_height + other.m_height ; h++) {
            for(int w = 0 ; w < m_width ; w++) {
                //První matice
                if(h < m_height) {
                    newMatrix->setValue(getValue(CPoint_2D(w, h)), CPoint_2D(w, h));
                }
                    //Druhá matice
                else {
                    newMatrix->setValue(other.getValue(CPoint_2D(w, h - m_height)), CPoint_2D(w, h));
                }
            }
        }
        return newMatrix;
    }
}
