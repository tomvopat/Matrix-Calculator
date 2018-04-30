//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CMATRIXFULL_H
#define PA2_SEM_CMATRIXFULL_H


#include "CMatrix.h"

#include <vector>

/**
 * Třáda pro reprezentaci husté matice
 */
class CMatrixFull : public CMatrix {
public:
    CMatrixFull(int height, int width);

    CMatrix* operator*(const CMatrix &other) const override;

    virtual double getValue(const CPoint_2D& point) const override;
    virtual void setValue(double value, const CPoint_2D& point);

    CMatrix* getTransposed() const override;
    CMatrix* cut(const CPoint_2D &leftTop, const CPoint_2D &rightBottom) const override;

    bool isRegular() const override;
    int getRank() const override;
    int getDeterminant() const override;
protected:
    std::vector<std::vector<double>> m_data;
};


#endif //PA2_SEM_CMATRIXFULL_H
