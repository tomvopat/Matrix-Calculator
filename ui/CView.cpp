//
// Created by Tomáš Vopat on 05.05.18.
//

#include <iostream>
#include <string>

#include "CView.h"

CView::CView(const CController &m_controller, const CModel &m_model) : m_controller(m_controller), m_model(m_model), m_run(false) {}

void CView::start() {
    m_run = true;

    while(m_run) {
        std::string input;
        std::getline(std::cin, input, ';');
        m_controller.command(input);
    }
}

void CView::stop() {
    m_run = false;
}

bool CView::show(const std::string &text) {
    std::cout << text << std::endl;
    return true;
}

bool CView::showFromModel(const std::string &id) {
    CMatrix* matrix = m_model.get(id);
    if(matrix == NULL) return false;
    std::cout << *matrix << std::endl;
    delete matrix;
}

bool CView::showTmpFromModel() {
    CMatrix* tmp = m_model.getTmp();
    if(tmp == NULL) return false;
    std::cout << *tmp << std::endl;
    delete tmp;
}
