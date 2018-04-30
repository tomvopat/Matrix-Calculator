//
// Created by Tomáš Vopat on 27.04.18.
//

#include "CPoint_2D.h"

CPoint_2D::CPoint_2D(int m_x, int m_y) : m_x(m_x), m_y(m_y) {}

int CPoint_2D::getX() const {
    return m_x;
}

int CPoint_2D::getY() const {
    return m_y;
}

bool CPoint_2D::operator <= (const CPoint_2D& other) const {
    return ((m_x <= other.m_x) && (m_y <= other.m_y));
}
