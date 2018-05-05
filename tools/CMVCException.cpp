//
// Created by Tomáš Vopat on 05.05.18.
//

#include "CMVCException.h"

CMVCException::CMVCException(const std::string &m_message) : m_message(m_message) {}

const std::string &CMVCException::getM_message() const {
    return m_message;
}
