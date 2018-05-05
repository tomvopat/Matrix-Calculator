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
    CModel();

    virtual ~CModel();

    bool add(const std::string& id, const CMatrix* matrix);
    bool remove(const std::string& id);
    CMatrix* get(const std::string& id);
    std::map<std::string, CMatrix*> getAll();
    bool contains(const std::string& id);

    void setTmp(const CMatrix* matrix);
    CMatrix* getTmp();
private:
    std::map<std::string, CMatrix*> m_data;
    CMatrix* m_tmp;
};


#endif //PA2_SEM_CMODEL_H
