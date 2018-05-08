//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CInvalidMatrixException.h"
#include <iostream>

CInvalidMatrixException::CInvalidMatrixException(const char *m_message) : m_message(m_message) {}

const char *CInvalidMatrixException::getM_message() const {
    return m_message;
}

std::ostream& operator << (std::ostream& os, const CInvalidMatrixException& ex) {
    return os << ex.getM_message();
}