//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CMODEL_H
#define PA2_SEM_CMODEL_H

#include <string>
#include <map>
#include "../matrix/CMatrix.h"


class CModel {
public:
    bool add(const std::string& id, const CMatrix* matrix);
    bool remove(const std::string& id);
    bool change(const std::string& id, const CMatrix* matrix);
    CMatrix* get(const std::string& id);
    bool contains(const std::string& id);
private:
    std::map<std::string, CMatrix*> m_data;
};


#endif //PA2_SEM_CMODEL_H
