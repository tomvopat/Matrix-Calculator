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

    virtual CMatrix* operator + (const CMatrix& other) const = 0;
    virtual CMatrix* operator - (const CMatrix& other) const = 0;
    virtual CMatrix* operator * (const CMatrix& other) const = 0;

    friend std::ostream& operator << (std::ostream& os, const CMatrix& matrix);

    /**
     * vrátí dynamicky alokovanou kopii této matice
     * @return
     */
    virtual CMatrix* duplicate() const = 0;

    /**
     * Prohodí řádky v matici zadané indexy 'i' a 'j'
     * @param i index řádku
     * @param j index řádku
     */
    virtual void swapRows(int i, int j) = 0;

    /**
     * Metoda pro výpis do proudu
     * @param os
     * @return
     */
    std::ostream& print(std::ostream& os) const;

    /**
     * Vrátí hodnotu na dané pozici v matici
     * @param point
     * @return
     */
    virtual double getValue(const CPoint_2D& point) const = 0;

    /**
     * Nastaví hodnotu na dané pozici v matici
     * @param value
     * @param point
     */
    virtual void setValue(double value, const CPoint_2D& point) = 0;

    /**
     * Vrátí velikost matice
     * @param height počet řádků
     * @param width počet sloupců
     */
    void getSize(int& height, int& width) const;

    /**
     * Vrátí počet řádků matice
     * @return
     */
    int getHeight() const;

    /**
     * Vrátí počet sloupců matice
     * @return
     */
    int getWidth() const;

    /**
     * Vrátí počet nenulových prvků
     * @return
     */
    int getNonZeroCount() const;

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
     * Vrátí hodnost matice
     * @return
     */
    int getRank() const;

    /**
     * Zjistí zda je zadaná matice regulární
     * @return true == regulární
     */
    bool isRegular() const;

    /**
     * Vrátí hodnotu determinantu matice
     * Vyhodí výjimku CInvalidMatrixException, pokud matice není čtvercová
     * @return
     */
    double getDeterminant() const;

    /**
     * Vrátí zGEMovanou matici
     * @return
     */
    CMatrix* gem() const;

    /**
     * Vrátí inverzní matici
     * pokud tato matice není regulární, vyhodí výjimku CInvalidMatrixException
     * Inverzní matice k regulární čtvercové matici A je adjugovaná matice, jejíž každý prvek je vydělen determinantem matice A
     * (Adjugovaná matice je transponovaná kofaktorová matice matice A)
     * @return
     */
    CMatrix* getInverse() const;

    /**
     * Vrátí TRUE, pokud je matice v horním stupňovitém tvaru
     * @return
     */
    bool isInRowEchelonForm() const;

    /**
     * Vrátí kofaktorovou matici
     * Kofaktorová matice je matice determinantů Beta(i,j) matic, kde na pozici (i,j) je determinant matice Beta(i,j) vynásobený (-1)^(i+j)
     * @return
     */
    CMatrix* cofactor() const;

    /**
     * Vrátí matici B(i,j)
     * matice B(i,j) vznikne z původní matice vynecháním i-tého řádku a j-tého sloupce
     * @param i řádkový index
     * @param j sloupcový index
     * @return
     */
    CMatrix* betaMatrix(int i, int j) const;

    /**
     * Vrátí true, pokud zadaný bod náleží do matice
     * bod (-1,0) = false
     * matice(3,7), bod(3,6) = false
     * ...
     * @param point
     * @return
     */
    bool isValid(const CPoint_2D& point) const;

protected:

    /**
     * Vrátí ukazatel na nově alokovanou matici stejného typu zadaných rozměrů
     * @param height počet řádků
     * @param width počet sloupců
     * @return
     */
    virtual CMatrix* newMatrix(int height, int width) const = 0;

    /**
     * Zjistí, je řádek vyplněn pouze nulama
     * @param i index řádku v matici
     * @return
     */
    virtual bool isZeroRow(int i) const = 0;

    /**
     * Sečte dvě matice
     * pokud tyto matice nelze sčítat, vyhodí výjimku CInvalidMatrixException
     * @param a
     * @param b
     * @param result výsledek
     */
    static void addition(const CMatrix& a, const CMatrix& b, CMatrix& result);

    /**
     * Odečte dvě matice
     * Pokud tyto matice nelze odečítat, vyhodí výjimku CInvalidMatrixException
     * @param a
     * @param b
     * @param result výsledek
     */
    static void subtraction(const CMatrix& a, const CMatrix& b, CMatrix& result);

    /**
     * Vynásobí dvě matice
     * Pokud tyto matice nejdou násobit, vyhodí výjimku CInvalidMatrixException
     * @param a levý činitel
     * @param b pravý činitel
     * @param result výsledek
     */
    static void multiplication(const CMatrix& a, const CMatrix& b, CMatrix& result);

    int m_height;
    int m_width;
    int m_nonZeroCount;
};


#endif //PA2_SEM_CMATRIX_H
