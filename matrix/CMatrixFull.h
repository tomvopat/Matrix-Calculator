//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CMATRIXFULL_H
#define PA2_SEM_CMATRIXFULL_H


#include "CMatrix.h"

#include <vector>

/**
 * Class for representing full matrix
 */
class CMatrixFull : public CMatrix {
public:
    CMatrixFull(int height, int width);
    CMatrix* duplicate() const override;

    CMatrix* operator + (const CMatrix& other) const override;
    CMatrix* operator - (const CMatrix& other) const override;
    CMatrix* operator * (const CMatrix& other) const override;

    void swapRows(int i, int j) override;

    double getValue(const CPoint_2D& point) const override;
    void setValue(double value, const CPoint_2D& point) override;

    CMatrix* getTransposed() const override;
    CMatrix* cut(const CPoint_2D &leftTop, const CPoint_2D &rightBottom) const override;
protected:
    CMatrix* newMatrix(int height, int width) const override;
    bool isZeroRow(int i) const override;

    std::vector<std::vector<double>> m_data;
};


#endif //PA2_SEM_CMATRIXFULL_H
