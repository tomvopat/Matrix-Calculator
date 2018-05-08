//
// Created by Tomáš Vopat on 03.05.18.
//

#include "Numbers.h"

#include <cmath>
#include <cfloat>

bool Numbers::isNull(double val) {
    return std::abs(val) <= DBL_EPSILON;
}

bool Numbers::equals(double x, double y) {
    return std::abs(x - y) <= DBL_EPSILON;
}

bool Numbers::isDouble(const std::string &s) {
    if(s.empty()) return false;
    bool dot = false;
    for(char c : s) {
        if(! std::isdigit(c)) {
            if((c == '.') && !dot) {
                dot = true;
            }
            else return false;
        }
    }
    return true;
}
