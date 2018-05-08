//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CMODEL_H
#define PA2_SEM_CMODEL_H

#include <string>
#include <map>
#include "../matrix/CMatrix.h"

/**
 * Třída pro reprezentaci modelu v MVC
 */

class CModel {
public:
    CModel();

    virtual ~CModel();

    /**
     * Adds data to model
     * @param id identifier
     * @param matrix data
     * @return
     */
    bool add(const std::string& id, const CMatrix* matrix);

    /**
     * removes data from model
     * @param id identifier
     * @return
     */
    bool remove(const std::string& id);

    /**
     * return data from model
     * @param id
     * @return
     */
    CMatrix* get(const std::string& id);

    /**
     * return all data from model
     * @return
     */
    std::map<std::string, CMatrix*> getAll();

    /**
     * return true if model contains object if certain identifier
     * @param id
     * @return
     */
    bool contains(const std::string& id);

    /**
     * sets temporary object
     * @param matrix
     */
    void setTmp(const CMatrix* matrix);

    /**
     * Returns temporary object
     * @return
     */
    CMatrix* getTmp();
private:
    std::map<std::string, CMatrix*> m_data;
    CMatrix* m_tmp;
};


#endif //PA2_SEM_CMODEL_H
