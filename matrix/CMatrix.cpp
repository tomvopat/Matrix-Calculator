//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrix.h"
#include "../tools/CInvalidMatrixException.h"
#include "CMatrixFull.h"

#include <iomanip>
#include <climits>
#include <cmath>

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

void CMatrix::addition(const CMatrix& a, const CMatrix& b, CMatrix& result) {
    for(int h = 0 ; h < a.m_height ; h++) {
        for(int w = 0 ; w < b.m_width ; w++) {
            result.setValue(a.getValue(CPoint_2D(w, h)) + b.getValue(CPoint_2D(w, h)), CPoint_2D(w, h));
        }
    }
}

void CMatrix::subtraction(const CMatrix& a, const CMatrix& b, CMatrix& result) {
    for(int h = 0 ; h < a.m_height ; h++) {
        for(int w = 0 ; w < b.m_width ; w++) {
            result.setValue(a.getValue(CPoint_2D(w, h)) - b.getValue(CPoint_2D(w, h)), CPoint_2D(w, h));
        }
    }
}

void CMatrix::multiplication(const CMatrix& a, const CMatrix& b, CMatrix& result) {
    for(int h = 0 ; h < a.m_height ; h++) {
        for(int w = 0 ; w < b.m_width ; w++) {
            double sum = 0;
            for(int n = 0 ; n < a.m_width ; n++) {
                sum += a.getValue(CPoint_2D(n, h)) * b.getValue(CPoint_2D(w, n));
            }
            result.setValue(sum, CPoint_2D(w, h));
        }
    }
}


std::ostream& operator << (std::ostream& os, const CMatrix& matrix) {
    matrix.print(os);
    return os;
}

std::ostream& CMatrix::print(std::ostream& os) const {
    for(int h = 0 ; h < m_height ; h++) {
        for(int w = 0 ; w < m_width ; w++) {
            os << std::setw(5) << getValue(CPoint_2D(w, h)) << std::setprecision(3) << " ";
        }
        os << "\n";
    }
    return os;
}

void CMatrix::getSize(int& height, int& width) const {
    height = m_height;
    width = m_width;
}

int CMatrix::getHeight() const {
    return m_height;
}

int CMatrix::getWidth() const {
    return m_width;
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

CMatrix* CMatrix::gem() const {
    CMatrix* newMatrix = this->duplicate();

    int h = 0; //inicializace řádkového pivota
    int k = 0; //inicializace sloupcového pivota

    while((h < newMatrix->m_height) && (k < newMatrix->m_width)) {
        int i_max = h;
        for(int i = h + 1; i < newMatrix->m_height ; i++) {
            if(std::abs(newMatrix->getValue(CPoint_2D(k, i))) > std::abs(newMatrix->getValue(CPoint_2D(k, i_max)))) {
                i_max = i;
            }
        }
        if(newMatrix->getValue(CPoint_2D(k, i_max)) == 0) {
            //žádný pivot v tomto sloupci
            k++;
        }
        else {
            newMatrix->swapRows(h, i_max);
            //Pro všechny řádky pod pivotem
            for(int i = h + 1 ; i < m_height ; i++) {
                double f = newMatrix->getValue(CPoint_2D(k, i)) / newMatrix->getValue(CPoint_2D(k, h));
                newMatrix->setValue(0, CPoint_2D(k, i));
                //pro všechny zbývající prvky v daném řádku
                for(int j = k + 1 ; j < newMatrix->m_width ; j++) {
                    newMatrix->setValue(newMatrix->getValue(CPoint_2D(j, i)) - newMatrix->getValue(CPoint_2D(j, h)) * f, CPoint_2D(j, i));
                }
            }
            h++;
            k++;
        }
    }
    return newMatrix;
}
