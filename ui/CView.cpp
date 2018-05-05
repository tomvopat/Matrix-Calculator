//
// Created by Tomáš Vopat on 05.05.18.
//

#include <iostream>
#include <string>

#include "CView.h"
#include "CController.h"
#include "CModel.h"
#include "../matrix/CMatrix.h"
#include "../tools/CMVCException.h"

CView::CView() : m_controller(NULL), m_model(NULL), m_run(false) {}

void CView::setController(CController *m_controller) {
    CView::m_controller = m_controller;
}

void CView::setModel(CModel *m_model) {
    CView::m_model = m_model;
}


void CView::start() {
    if(!m_model || !m_controller) throw CMVCException("Není nastaven model nebo controller.");
    m_run = true;

    std::cout << "Welcome to matrix calculator!" << std::endl;

    while(m_run) {
        m_controller->command(getInput());
    }
}

void CView::stop() {
    m_run = false;
}

std::string CView::getInput() {
    std::string input;
    std::getline(std::cin, input, ';');
    return input;
}

bool CView::show(const std::string &text) {
    std::cout << text << std::endl;
    return true;
}

bool CView::showFromModel(const std::string &id) {
    CMatrix* matrix = m_model->get(id);
    if(matrix == NULL) return false;
    std::cout << *matrix << std::endl;
    delete matrix;
    return true;
}

bool CView::showTmpFromModel() {
    CMatrix* tmp = m_model->getTmp();
    if(tmp == NULL) return false;
    std::cout << *tmp << std::endl;
    delete tmp;
    return true;
}