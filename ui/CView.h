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

    /**
     * Nastaví controller
     * @param m_controller
     */
    void setController(CController *m_controller);

    /**
     * Nastaví model
     * @param m_model
     */
    void setModel(CModel *m_model);

    /**
     * Spustí uživatelské rozhraní
     */
    void start();

    /**
     * Zastaví uživatelské rozhraní
     */
    void stop();

    /**
     * Vrátí uživatelský vstup
     * @return
     */
    std::string getInput();

    /**
     * Zobrazí v uživatelském rozhraní text
     * @param text
     * @return
     */
    bool show(const std::string& text);

    /**
     * Zobrazí data z modelu
     * @param id
     * @return
     */
    bool showFromModel(const std::string& id);

    /**
     * Zobrazí všechna data z modelu
     */
    void showAllFromModel();

    /**
     * Zobrazí temporary object z modelu
     * @return
     */
    bool showTmpFromModel();
private:
    CController* m_controller;
    CModel* m_model;

    bool m_run;
};


#endif //PA2_SEM_CVIEW_H
