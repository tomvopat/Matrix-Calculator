//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrixSparse.h"
#include "../tools/CInvalidMatrixException.h"

CMatrixSparse::CMatrixSparse(int m_height, int m_width) : CMatrix(m_height, m_width) {

}

CMatrix* CMatrixSparse::duplicate() const {
    return new CMatrixSparse(*this);
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
    CMatrixSparse* newMatrix = new CMatrixSparse(m_width, m_height);
    for(auto iterH = m_data.begin() ; iterH != m_data.end() ; ++iterH) {
        for(auto iterW = iterH->second.begin() ; iterW != iterH->second.end() ; ++iterW) {
            newMatrix->setValue(iterW->second, CPoint_2D(iterH->first, iterW->first));
        }
    }
    return newMatrix;
}

CMatrix *CMatrixSparse::cut(const CPoint_2D &leftTop, const CPoint_2D &rightBottom) const {
    if(!isValid(leftTop) || !isValid(rightBottom)) throw CInvalidMatrixException("Body nenáleží matici");
    if(! (leftTop <= rightBottom)) throw CInvalidMatrixException("Zadán neplatný výřez.");

    CMatrixSparse* newMatrix = new CMatrixSparse(rightBottom.getY() - leftTop.getY() + 1, rightBottom.getX() - leftTop.getX() + 1);

    auto lowerH = m_data.lower_bound(leftTop.getY());
    auto upperH = m_data.upper_bound(rightBottom.getY());
    while(lowerH != upperH) {
        auto lowerW = lowerH->second.lower_bound(leftTop.getX());
        auto upperW = lowerH->second.upper_bound(rightBottom.getX());
        while(lowerW != upperW) {
            newMatrix->setValue(lowerW->second, CPoint_2D(lowerW->first - leftTop.getX(), lowerH->first - leftTop.getY()));
            ++lowerW;
        }
        ++lowerH;
    }
    return newMatrix;
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
