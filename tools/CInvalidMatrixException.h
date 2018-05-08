//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CINVALIDMATRIX_H
#define PA2_SEM_CINVALIDMATRIX_H

#include <iostream>

/**
 * Class represent exception thrown when some error is caused in classes CMatrix
 */

class CInvalidMatrixException : public std::exception {
public:
    CInvalidMatrixException(const char *m_message);
    const char *getM_message() const;
    friend std::ostream& operator << (std::ostream& os, const CInvalidMatrixException& ex);

private:
    const char* m_message;
};


#endif //PA2_SEM_CINVALIDMATRIX_H
