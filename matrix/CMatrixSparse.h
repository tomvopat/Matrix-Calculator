//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CMATRIXSPARSE_H
#define PA2_SEM_CMATRIXSPARSE_H


#include "CMatrix.h"

#include <map>

/**
 * Třída pro reprezentaci řídké matice
 */
class CMatrixSparse : public CMatrix {

public:
    CMatrixSparse(int m_height, int m_width);

    CMatrix *operator*(const CMatrix &other) const override;

    double getValue(const CPoint_2D &point) const override;
    void setValue(double value, const CPoint_2D &point) override;

    CMatrix *getTransposed() const override;
    CMatrix *cut(const CPoint_2D &leftTop, const CPoint_2D &rightBottom) const override;

    bool isRegular() const override;
    int getRank() const override;
    int getDeterminant() const override;

protected:
    std::map<int, std::map<int, double>> m_data;
};


#endif //PA2_SEM_CMATRIXSPARSE_H