//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CMatrix.h"
#include "../tools/CInvalidMatrixException.h"

CMatrix::CMatrix(int height, int width) {
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

int CMatrix::getHeight() const {
    return m_height;
}

int CMatrix::getWidth() const {
    return m_width;
}
