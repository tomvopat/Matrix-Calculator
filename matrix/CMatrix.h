//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CMATRIX_H
#define PA2_SEM_CMATRIX_H

#include "../tools/CPoint_2D.h"

#include <iostream>


/**
 * Main class for representing matrix
 */
class CMatrix {
public:
    CMatrix(int m_height, int m_width);
    virtual ~CMatrix() = default;

    virtual CMatrix* operator + (const CMatrix& other) const = 0;
    virtual CMatrix* operator - (const CMatrix& other) const = 0;
    virtual CMatrix* operator * (const CMatrix& other) const = 0;

    friend std::ostream& operator << (std::ostream& os, const CMatrix& matrix);

    /**
     * returns dynamically alocated copy of this matrix
     * @return
     */
    virtual CMatrix* duplicate() const = 0;

    /**
     * swap rows in matrix identified by 'i' and 'j' indices
     * @param i row index
     * @param j row index
     */
    virtual void swapRows(int i, int j) = 0;

    /**
     * Method for output stream
     * @param os
     * @return
     */
    std::ostream& print(std::ostream& os) const;

    /**
     * Returns value in matrix on exact position
     * @param point
     * @return
     */
    virtual double getValue(const CPoint_2D& point) const = 0;

    /**
     * Sets value in matrix to exact value
     * @param value
     * @param point
     */
    virtual void setValue(double value, const CPoint_2D& point) = 0;

    /**
     * Returns matrix size
     * @param height row count
     * @param width coulmn count
     */
    void getSize(int& height, int& width) const;

    /**
     * Returns row count
     * @return
     */
    int getHeight() const;

    /**
     * Returns column count
     * @return
     */
    int getWidth() const;

    /**
     * Returns non-zero row count
     * @return
     */
    int getNonZeroCount() const;

    /**
     * Return transposed matrix
     * @return
     */
    virtual CMatrix* getTransposed() const = 0;

     /**
     * Maerge two matrices
     * @param other matrix to merge
     * @param horizontally ? next to each other : below each other
     * @return merged matrix
     */
    CMatrix* merge(const CMatrix& other, bool horizontally) const;

    /**
     * crop the matrix
     * @param leftTop left-top point
     * @param rightBottom bottom-right point
     * @return cropped matrix
     */
    virtual CMatrix* cut(const CPoint_2D& leftTop, const CPoint_2D& rightBottom) const = 0;

    /**
     * Return rank of the matrix
     * @return
     */
    int getRank() const;

    /**
     * Check for the matrix regularity
     * @return true == regulární
     */
    bool isRegular() const;

    /**
     * Vrátí hodnotu determinantu matice
     * Return determinant of the matrix
     * Throws exception CInvalidMatrixException, if it is NOT square matrix
     * @return
     */
    double getDeterminant() const;

    /**
     * Returns matrix after gaussian elimination
     * @return
     */
    CMatrix* gem() const;

    /**
     * Return inverted matrix
     * if this matrix is NOT regular, throw exception CInvalidMAtrixException
     * The adjoint matrix is the transpose of the cofactor matrix.
     * The cofactor matrix is the matrix of determinants of the minors Aij multiplied by -1i+j.
     * The i,j'th minor of A is the matrix A without the i'th column or the j'th row.
     * @return
     */
    CMatrix* getInverse() const;

    /**
     * Return TRUE if the matrix is in row-echelon form
     * @return
     */
    bool isInRowEchelonForm() const;

    /**
     * Return cofactor matrix
     * Cofactor matrix is matrix composed of determinant matrices Beta(i,j),
     * where on position (i,j) is det of matrix Beta(i,j) multiplied by (-1)^(i+j)
     * @return
     */
    CMatrix* cofactor() const;

    /**
     * Return matrix Beta(i,j)
     * Matrix Beta(i,j) is Matrix original matrix A with skipped i-th row and j-th column
     * @param i row index
     * @param j column index
     * @return
     */
    CMatrix* betaMatrix(int i, int j) const;

    /**
     * Returns TRUE, if the point is in the matrix
     * point (-1,0) = false
     * matrix(3,7), point(3,6) = false
     * ...
     * @param point
     * @return
     */
    bool isValid(const CPoint_2D& point) const;

protected:

    /**
     * Return pointer to newly alocated matrix of the same type (full / sparse)
     * @param height row count
     * @param width column count
     * @return
     */
    virtual CMatrix* newMatrix(int height, int width) const = 0;

    /**
     * Returns TRUE, if the row 'i' if filled with zeros
     * @param i row index
     * @return
     */
    virtual bool isZeroRow(int i) const = 0;

    /**
     * Add to matrices
     * Its not possible to add two matrices with different sizes - throws CInvalidMAtrixException
     * @param a
     * @param b
     * @param result
     */
    static void addition(const CMatrix& a, const CMatrix& b, CMatrix& result);

    /**
     * subtract to matrices
     * Its not possible to subtract two matrices with different sizes - throws CInvalidMAtrixException
     * @param a
     * @param b
     * @param result
     */
    static void subtraction(const CMatrix& a, const CMatrix& b, CMatrix& result);

    /**
     * Multiple two matrices
     * It is possible to multiple two matrices, if the column count of the first matrix
     * is equal to the row count of the second matrix
     * @param a
     * @param b
     * @param result
     */
    static void multiplication(const CMatrix& a, const CMatrix& b, CMatrix& result);

    int m_height;
    int m_width;
    int m_nonZeroCount;
};


#endif //PA2_SEM_CMATRIX_H
