//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CVECTORFULL_H
#define PA2_SEM_CVECTORFULL_H


#include "../CMatrixFull.h"
#include "CVector.h"

class CVectorFull : public CVector, public CMatrixFull{
public:
    CVectorFull(int width);

    CVector *operator+(const CVector &other) const override;
    CVector *operator-(const CVector &other) const override;
    CVector *operator*(int val) const override;

protected:
};


#endif //PA2_SEM_CVECTORFULL_H
