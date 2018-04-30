//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CMATRIX_H
#define PA2_SEM_CMATRIX_H

#include "../tools/CPoint_2D.h"

/**
 * Hlavní třída pro reprezentaci matice
 */
class CMatrix {
public:
    CMatrix(int m_height, int m_width);

    virtual CMatrix operator + (const CMatrix& other) const = 0;
    virtual CMatrix operator - (const CMatrix& other) const = 0;
    virtual CMatrix operator * (const CMatrix& other) const = 0;

    virtual double getValue(const CPoint_2D& point) const = 0;
    virtual double& getValue(const CPoint_2D& point) = 0;
    int getHeight() const;
    int getWidth() const;

    /**
     * Vrátí transponovanou matici
     * @return
     */
    virtual CMatrix getTransposed() const = 0;
    /**
     * Sloučí dvě matice
     * @param other matice ke sloučení
     * @param horizontally ? vedle sebe : pod sebou
     * @return sloučená matice
     */
    virtual CMatrix merge(const CMatrix& other, bool horizontally) const = 0;
    /**
     * Ořízne matici podle zadaných dvou bodů (včetně)
     * @param leftTop levý horní bod
     * @param rightBottom pravý dolní bod
     * @return oříznutá matice
     */
    virtual CMatrix cut(const CPoint_2D& leftTop, const CPoint_2D& rightBottom) const = 0;

    /**
     * Vrátí rozměry matice
     * @param height výška
     * @param width šířka
     */
    virtual void getSize(int& height, int& width) const = 0;

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
    int m_height;
    int m_width;
};


#endif //PA2_SEM_CMATRIX_H
