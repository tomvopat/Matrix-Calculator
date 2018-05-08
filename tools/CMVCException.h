//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CMVCEXCEPTION_H
#define PA2_SEM_CMVCEXCEPTION_H


#include <string>

/**
 * Třída výjimky, která je vyhazována v případě chyby v MVC
 */

class CMVCException : public std::exception {
public:
    CMVCException(const std::string &m_message);

    const std::string &getM_message() const;

private:
    const std::string m_message;
};


#endif //PA2_SEM_CMVCEXCEPTION_H
