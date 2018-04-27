//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CInvalidMatrixException.h"

CInvalidMatrixException::CInvalidMatrixException(const char *m_message) : m_message(m_message) {}

const char *CInvalidMatrixException::getM_message() const {
    return m_message;
}
