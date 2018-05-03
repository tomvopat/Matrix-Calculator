//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrixSparse.h"
#include "../tools/CInvalidMatrixException.h"
#include "../tools/Numbers.h"

CMatrixSparse::CMatrixSparse(int m_height, int m_width) : CMatrix(m_height, m_width) {

}

CMatrix* CMatrixSparse::duplicate() const {
    return new CMatrixSparse(*this);
}

CMatrix* CMatrixSparse::operator + (const CMatrix& other) const {

    if((m_width != other.getWidth()) || (m_height != other.getHeight())) throw CInvalidMatrixException("Nelze sčítat matice různých rozměrů.");
    CMatrixSparse* newMatrix = new CMatrixSparse(m_height, m_width);
    CMatrix::addition(*this, other, *newMatrix);
    return newMatrix;
}

CMatrix* CMatrixSparse::operator - (const CMatrix& other) const {
    if((m_width != other.getWidth()) || (m_height != other.getHeight())) throw CInvalidMatrixException("Nelze odčítat matice různých rozměrů.");
    CMatrixSparse* newMatrix = new CMatrixSparse(m_height, m_width);
    CMatrix::subtraction(*this, other, *newMatrix);
    return newMatrix;
}

CMatrix* CMatrixSparse::operator * (const CMatrix& other) const {
    if(m_width != other.getHeight()) throw CInvalidMatrixException("Tyto matice nelze násobit");
    CMatrixSparse* newMatrix = new CMatrixSparse(m_height, other.getWidth());
    CMatrix::multiplication(*this, other, *newMatrix);
    return newMatrix;
}

void CMatrixSparse::swapRows(int i, int j) {
    if((i >= m_height) || (j >= m_height)) throw CInvalidMatrixException("Neplatné řádkové indexy.");

    auto iterI = m_data.find(i);
    auto iterJ = m_data.find(j);

    //radek 'i' neni definovany
    if(iterI == m_data.end()) {
        //radek 'j' take neni definovany
        if(iterJ == m_data.end()) {}
        else {
            std::map<int, double> tmpJ(iterJ->second);
            m_data.erase(j);
            m_data[i] = tmpJ;
        }
    }
    //radek 'j' neni definovany
    else if(iterJ == m_data.end()) {
        std::map<int, double> tmpI(iterI->second);
        m_data.erase(i);
        m_data[j] = tmpI;

    }
    //oba radky jsou definovane
    else {
        std::map<int, double> tmpI(iterI->second);
        std::map<int, double> tmpJ(iterJ->second);
        m_data.erase(i);
        m_data.erase(j);
        m_data[j] = tmpI;
        m_data[i] = tmpJ;
    }
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
    if(Numbers::isNull(value)) {
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
