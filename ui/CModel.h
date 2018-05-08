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

    /**
     * Přidá data do modelu
     * @param id identifikátor
     * @param matrix data
     * @return
     */
    bool add(const std::string& id, const CMatrix* matrix);

    /**
     * Odstraní data z modelu
     * @param id identifikátor
     * @return
     */
    bool remove(const std::string& id);

    /**
     * Vrátí data z modelu
     * @param id
     * @return
     */
    CMatrix* get(const std::string& id);

    /**
     * Vrátí všechna data z modelu
     * @return
     */
    std::map<std::string, CMatrix*> getAll();

    /**
     * Vrátí TRUE, pokud model obsahuje objekt s daným identifikátorem
     * @param id
     * @return
     */
    bool contains(const std::string& id);

    /**
     * Nastaví temporary object
     * @param matrix
     */
    void setTmp(const CMatrix* matrix);

    /**
     * Vrátí temporary object
     * @return
     */
    CMatrix* getTmp();
private:
    std::map<std::string, CMatrix*> m_data;
    CMatrix* m_tmp;
};


#endif //PA2_SEM_CMODEL_H
