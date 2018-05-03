//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrix.h"
#include "../tools/CInvalidMatrixException.h"
#include "CMatrixFull.h"
#include "../tools/Numbers.h"

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

int CMatrix::getRank() const {
    if(! isInRowEchelonForm()) {
        CMatrix* mm = gem();
        int rank = mm->getRank();
        delete mm;
        return rank;
    }

    int i = m_height;
    while(i > 0) {
        if(! isZeroRow(i - 1)) break;
        i--;
    }
    return i;
}

bool CMatrix::isRegular() const {
    //Matice s nulovou velikostí není regulární
    if(m_height == 0) return false;

    int n = m_width;
    while(n > 0) {
        if(! Numbers::isNull(getValue(CPoint_2D(m_width - n, 0)))) break;
        n--;
    }

    if(getRank() == n) return true;

    return false;
}

//source: https://www.cs.rochester.edu/~brown/Crypto/assts/projects/adj.html
double CMatrix::getDeterminant() const {
    CMatrix* mm = gem();
    if(! mm->isRegular()) {
        delete mm;
        throw CInvalidMatrixException("Nelze počítat determinant neregulární matice.");
    }

    int n = mm->getRank();
    int w = 0;

    while(w < mm->getWidth()) {
        if(! Numbers::isNull(mm->getValue(CPoint_2D(w, 0)))) break;
        w++;
    }

    CMatrix* newMatrix = mm->cut(CPoint_2D(w, 0), CPoint_2D(mm->getWidth() - 1, n - 1));
    delete mm;
    double det = newMatrix->determinantRecursive();
    delete newMatrix;
    return det;
}

double CMatrix::determinantRecursive() const {
    if(m_height == 1) return getValue(CPoint_2D(0,0));
    else if(m_height == 2) {
        return getValue(CPoint_2D(0,0)) * getValue(CPoint_2D(1,1)) - getValue(CPoint_2D(1,0)) * getValue(CPoint_2D(0,1));
    }
    else {
        double det = 0;
        for(int j1 = 0 ; j1 < m_height ; j1++) {
            CMatrix* newMatrix = cut(CPoint_2D(1,1), CPoint_2D(m_height - 1, m_width - 1));
            for(int i = 1 ; i < m_height ; i++) {
                int j2 = 0;
                for(int j = 0 ; j < m_height ; j++) {
                    if(j == j1) continue;
                    newMatrix->setValue(getValue(CPoint_2D(i, j)), CPoint_2D(i - 1, j2));
                    j2++;
                }
            }
            det += pow(-1.0, j1 + 2.0) * getValue(CPoint_2D(0, j1)) * newMatrix->determinantRecursive();
            delete newMatrix;
        }
        return det;
    }
}

CMatrix* CMatrix::gem() const {
    CMatrix* newMatrix = duplicate();

    int h = 0; //inicializace řádkového pivota
    int k = 0; //inicializace sloupcového pivota

    while((h < newMatrix->m_height) && (k < newMatrix->m_width)) {
        int i_max = h;
        for(int i = h + 1; i < newMatrix->m_height ; i++) {
            if(std::abs(newMatrix->getValue(CPoint_2D(k, i))) > std::abs(newMatrix->getValue(CPoint_2D(k, i_max)))) {
                i_max = i;
            }
        }
        if(Numbers::isNull(newMatrix->getValue(CPoint_2D(k, i_max)))) {
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

CMatrix* CMatrix::invert() const {

    //todo

    return NULL;
}

bool CMatrix::isInRowEchelonForm() const {
    int h = 0;
    int w = 0;

    while((h < m_height) && (w < m_width)) {
        for(int i = h + 1 ; i < m_height ; i++) {
            if(! Numbers::isNull(getValue(CPoint_2D(w, i)))) return false;
        }
        if(! Numbers::isNull(getValue(CPoint_2D(w, h)))) h++;
        w++;
    }
    return true;
}
