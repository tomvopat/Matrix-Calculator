//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CPoint_2D.h"

CPoint_2D::CPoint_2D(int m_x, int m_y) : m_x(m_x), m_y(m_y) {}

int CPoint_2D::getM_x() const {
    return m_x;
}

int CPoint_2D::getM_y() const {
    return m_y;
}
