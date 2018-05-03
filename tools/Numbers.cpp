//
// Created by Tomáš Vopat on 03.05.18.
//

#include "Numbers.h"

#include <cmath>
#include <cfloat>

bool Numbers::isNull(double val) {
    return abs(val) <= DBL_EPSILON;
}