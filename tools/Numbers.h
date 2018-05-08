//
// Created by Tomáš Vopat on 03.05.18.
//

#ifndef PA2_SEM_NUMBERS_H
#define PA2_SEM_NUMBERS_H


#include <string>

/**
 * Statická třída pro práci s čísly, převážně doubly
 */

class Numbers {
public:

    /**
     * Porovnání, zda je double roven 0
     * @param val
     * @return
     */
    static bool isNull(double val);

    /**
     * Porovnání, zda jsou si dva doubly rovny
     * @param x
     * @param y
     * @return
     */
    static bool equals(double x, double y);

    /**
     * Vrací TRUE, pokud je ve stringu uložený double
     * @param s
     * @return
     */
    static bool isDouble(const std::string& s);
private:

};


#endif //PA2_SEM_NUMBERS_H
