//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CVIEW_H
#define PA2_SEM_CVIEW_H

#include <string>

class CModel;
class CController;

class CView {
public:
    CView();
    void setController(CController *m_controller);
    void setModel(CModel *m_model);
    void start();
    void stop();
    std::string getInput();
    bool show(const std::string& text);
    bool showFromModel(const std::string& id);
    bool showTmpFromModel();
private:
    CController* m_controller;
    CModel* m_model;

    bool m_run;
};


#endif //PA2_SEM_CVIEW_H
