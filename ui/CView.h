//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CVIEW_H
#define PA2_SEM_CVIEW_H

#include <string>

#include "CController.h"
#include "CModel.h"

class CView {
public:
    CView(const CController &m_controller, const CModel &m_model);

    void start();
    void stop();
    bool show(const std::string& text);
    bool showFromModel(const std::string& id);
    bool showTmpFromModel();
private:
    CController m_controller;
    CModel m_model;

    bool m_run;
};


#endif //PA2_SEM_CVIEW_H
