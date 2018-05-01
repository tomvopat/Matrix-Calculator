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
public:
    CVector(int m_width);

    virtual CVector* operator + (const CVector& other) const = 0;
    virtual CVector* operator - (const CVector& other) const = 0;
    virtual CVector* operator * (int val) const = 0;

    bool isRegular() const override;
    int getRank() const override;
    int getDeterminant() const override;
protected:
};


#endif //PA2_SEM_CVECTOR_H
