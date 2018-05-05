//
// Created by Tomáš Vopat on 05.05.18.
//

#include "CModel.h"
#include <vector>

CModel::CModel() : m_tmp(NULL) {}

CModel::~CModel() {
    for(auto iter : m_data) delete iter.second;
}

bool CModel::add(const std::string &id, const CMatrix *matrix) {
    return m_data.insert(make_pair(id, matrix->duplicate())).second;
}

bool CModel::remove(const std::string &id) {
    auto iter = m_data.find(id);
    if(iter == m_data.end()) return false;
    delete iter->second;
    m_data.erase(iter);
    return true;
}

CMatrix *CModel::get(const std::string &id) {
    auto iter = m_data.find(id);
    if(iter == m_data.end()) return NULL;
    return iter->second->duplicate();
}

std::map<std::string, CMatrix*> CModel::getAll() {
    return std::map<std::string, CMatrix*>(m_data);
}

bool CModel::contains(const std::string &id) {
    auto iter = m_data.find(id);
    if(iter == m_data.end()) return false;
    return true;
}

void CModel::setTmp(const CMatrix *matrix) {
    delete m_tmp;
    m_tmp = matrix->duplicate();
}

CMatrix *CModel::getTmp() {
    if(m_tmp == NULL) return NULL;
    return m_tmp->duplicate();
}
