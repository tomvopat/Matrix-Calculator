//
// Created by Tomáš Vopat on 27.04.18.
//

#ifndef PA2_SEM_CINVALIDMATRIX_H
#define PA2_SEM_CINVALIDMATRIX_H


class CInvalidMatrixException {
public:
    CInvalidMatrixException(const char *m_message);

    const char *getM_message() const;

private:
    const char* m_message;
};


#endif //PA2_SEM_CINVALIDMATRIX_H
