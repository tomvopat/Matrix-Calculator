//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CPOINT_2D_H
#define PA2_SEM_CPOINT_2D_H

/**
 * Class represent point in 2D space
 */
class CPoint_2D {
public:
    CPoint_2D(int m_x, int m_y);
    int getX() const;
    int getY() const;

    /**
     * Compares two points
     * Return true if (X1 <= X2) && (Y1 >= Y2)
     * @param other
     * @return
     */
    bool operator <= (const CPoint_2D& other) const;
private:
    int m_x;
    int m_y;
};


#endif //PA2_SEM_CPOINT_2D_H
