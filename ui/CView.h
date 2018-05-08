//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CVIEW_H
#define PA2_SEM_CVIEW_H

#include <string>

class CModel;
class CController;

/**
 * Třída pro reprezentaci view v MVC
 */

class CView {
public:
    CView();
    void setController(CController *m_controller);
    void setModel(CModel *m_model);

    /**
     * Starts UI
     */
    void start();

    /**
     * Stops UI
     */
    void stop();

    /**
     * return users input
     * @return
     */
    std::string getInput();

    /**
     * show text in UI
     * @param text
     * @return
     */
    bool show(const std::string& text);

    /**
     * shows data from model
     * @param id
     * @return
     */
    bool showFromModel(const std::string& id);

    /**
     * shows all the data from model
     */
    void showAllFromModel();

    /**
     * shows temporary object from model
     * @return
     */
    bool showTmpFromModel();
private:
    CController* m_controller;
    CModel* m_model;

    bool m_run;
};


#endif //PA2_SEM_CVIEW_H
