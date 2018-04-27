//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CPOINT_2D_H
#define PA2_SEM_CPOINT_2D_H

/**
 * Represents point in two dimension space
 */
class CPoint_2D {
public:
    CPoint_2D(int m_x, int m_y);

    int getM_x() const;
    int getM_y() const;
private:
    int m_x;
    int m_y;
};


#endif //PA2_SEM_CPOINT_2D_H
