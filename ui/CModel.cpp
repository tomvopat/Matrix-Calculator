//
// Created by Tomáš Vopat on 05.05.18.
//

#include "CModel.h"

bool CModel::add(const std::string &id, const CMatrix *matrix) {
    return m_data.insert(make_pair(id, matrix->duplicate())).second;
}

bool CModel::remove(const std::string &id) {
    return (m_data.erase(id) == 1);
}

CMatrix *CModel::get(const std::string &id) {
    auto iter = m_data.find(id);
    if(iter == m_data.end()) return NULL;
    return *iter;
}

bool CModel::contains(const std::string &id) {
    auto iter = m_data.find(id);
    if(iter == m_data.end()) return false;
    return true;
}
