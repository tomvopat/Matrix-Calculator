//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CVector.h"
#include "../../tools/CInvalidMatrixException.h"

CVector::CVector(int m_width) : CMatrix(0, m_width) {

}

bool CVector::isRegular() const {
    //Vektor není regulární matice
    return false;
}

int CVector::getRank() const {
    //Jeden vektor je vždy lineárně nezávislý a jeho stupeň je 1
    return 1;
}

int CVector::getDeterminant() const {
    //Vektor není regulární matice, a proto determinant nemůže být spočítán
    throw CInvalidMatrixException("Determinant nelze počítat pro singulární matice.");
}
