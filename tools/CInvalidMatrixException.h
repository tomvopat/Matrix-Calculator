//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CINVALIDMATRIX_H
#define PA2_SEM_CINVALIDMATRIX_H

#include <iostream>

class CInvalidMatrixException {
public:
    CInvalidMatrixException(const char *m_message);
    const char *getM_message() const;
    friend std::ostream& operator << (std::ostream& os, const CInvalidMatrixException& ex);

private:
    const char* m_message;
};


#endif //PA2_SEM_CINVALIDMATRIX_H