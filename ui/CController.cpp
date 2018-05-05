//
// Created by Tomáš Vopat on 05.05.18.
//


#include <sstream>
#include "CController.h"
#include "../tools/CMVCException.h"

CController::CController() : m_view(NULL), m_model(NULL) {}

void CController::command(const std::string &s) {
    if(!m_view || !m_model) throw CMVCException("Chybí view nebo model.");

    std::stringstream ss(s);

    while(! ss.eof()) {
        std::string part;
        ss >> part;


    }
}

void CController::setView(CView *m_view) {
    CController::m_view = m_view;
}

void CController::setModel(CModel *m_model) {
    CController::m_model = m_model;
}
