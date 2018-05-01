//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrixSparse.h"
#include "../tools/CInvalidMatrixException.h"

CMatrixSparse::CMatrixSparse(int m_height, int m_width) : CMatrix(m_height, m_width) {

}

CMatrix *CMatrixSparse::operator*(const CMatrix &other) const {
    return nullptr;
}

double CMatrixSparse::getValue(const CPoint_2D &point) const {
    if(! isValid(point)) throw CInvalidMatrixException("Bod nenáleží matici.");
    auto iterH = m_data.find(point.getY());
    if(iterH == m_data.end()) return 0;
    auto iterW = iterH->second.find(point.getX());
    if(iterW == iterH->second.end()) return 0;
    return iterW->second;
}

void CMatrixSparse::setValue(double value, const CPoint_2D &point) {
    if(! isValid(point)) throw CInvalidMatrixException("Bod nenáleží matici.");
    if(value == 0) {
        //Musíme zkontrolovat, zda tam takový prvek už není a případně ho smazat!
        auto iterH = m_data.find(point.getY());
        if(iterH != m_data.end()) {
            auto iterW = iterH->second.find(point.getX());
            if(iterW != iterH->second.end()) {
                iterH->second.erase(iterW);
                m_nonZeroCount--;
            }
        }
        return;
    }
    m_data[point.getY()][point.getX()] = value;
    m_nonZeroCount++;
}

CMatrix *CMatrixSparse::getTransposed() const {
    return nullptr;
}

CMatrix *CMatrixSparse::cut(const CPoint_2D &leftTop, const CPoint_2D &rightBottom) const {
    return nullptr;
}

bool CMatrixSparse::isRegular() const {
    return false;
}

int CMatrixSparse::getRank() const {
    return 0;
}

int CMatrixSparse::getDeterminant() const {
    return 0;
}
