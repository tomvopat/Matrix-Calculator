//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CMATRIX_H
#define PA2_SEM_CMATRIX_H

#include "../tools/CPoint_2D.h"

#include <iostream>

/**
 * Hlavní třída pro reprezentaci matice
 */
class CMatrix {
public:
    CMatrix(int m_height, int m_width);
    virtual ~CMatrix() = default;

    CMatrix* operator + (const CMatrix& other) const;
    CMatrix* operator - (const CMatrix& other) const;
    virtual CMatrix* operator * (const CMatrix& other) const = 0;
    friend std::ostream& operator << (std::ostream& os, const CMatrix& matrix);

    virtual std::ostream& print(std::ostream& os) const = 0;

    virtual double getValue(const CPoint_2D& point) const = 0;
    virtual void setValue(double value, const CPoint_2D& point) = 0;

    void getSize(int& height, int& width) const;

    /**
     * Vrátí transponovanou matici
     * @return
     */
    virtual CMatrix* getTransposed() const = 0;
    /**
     * Sloučí dvě matice
     * @param other matice ke sloučení
     * @param horizontally ? vedle sebe : pod sebou
     * @return sloučená matice
     */
    CMatrix* merge(const CMatrix& other, bool horizontally) const;
    /**
     * Ořízne matici podle zadaných dvou bodů (včetně)
     * @param leftTop levý horní bod
     * @param rightBottom pravý dolní bod
     * @return oříznutá matice
     */
    virtual CMatrix* cut(const CPoint_2D& leftTop, const CPoint_2D& rightBottom) const = 0;

    /**
     * Zjistí zda je zadaná matice regulární
     * @return true == regulární
     */
    virtual bool isRegular() const = 0;
    /**
     * Vrátí hodnost matice
     * Vyhodí výjimku CInvalidMatrixException, pokud matice není čtvercová
     * @return
     */
    virtual int getRank() const = 0;
    /**
     * Vrátí hodnotu determinantu matice
     * Vyhodí výjimku CInvalidMatrixException, pokud matice není regulární
     * @return
     */
    virtual int getDeterminant() const = 0;
protected:
    /**
     * Vrátí true, pokud zadaný bod náleží do matice
     * bod (-1,0) = false
     * matice(3,7), bod(3,6) = false
     * ...
     * @param point
     * @return
     */
    bool isValid(const CPoint_2D& point) const;

    int m_height;
    int m_width;
    int m_nonZeroCount;
};


#endif //PA2_SEM_CMATRIX_H
