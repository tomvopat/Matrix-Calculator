//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CVECTOR_H
#define PA2_SEM_CVECTOR_H


#include "../CMatrix.h"

/**
 * Třída pro reprezentaci vektoru
 */
class CVector : CMatrix {
    CVector(int m_width);

    bool isRegular() const override;
    int getRank() const override;
    int getDeterminant() const override;
};


#endif //PA2_SEM_CVECTOR_H
