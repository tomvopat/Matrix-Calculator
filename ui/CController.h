//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CCONTROLLER_H
#define PA2_SEM_CCONTROLLER_H

#include <string>

class CView;
class CModel;
class CMatrix;

/**
 * Třída pro rezprezentaci controlleru v MVC
 */

class CController {
private:
    enum COMMAND_TYPE {
        COMMAND_TYPE__BEGIN = 0,
        COMMAND_TYPE_EXIT = COMMAND_TYPE__BEGIN,
        COMMAND_TYPE_HELP,
        COMMAND_TYPE_LIST,
        COMMAND_TYPE_PRINT,
        COMMAND_TYPE_DOUBLE = 10,
        COMMAND_TYPE_BRACKET,
        COMMAND_TYPE_EQUATOR = 20,
        COMMAND_TYPE_OPERATOR,
        COMMAND_TYPE_SCAN,
        COMMAND_TYPE_MATRIX = 30,
        COMMAND_TYPE_ID,
        COMMAND_TYPE_MERGE,
        COMMAND_TYPE_CUT,
        COMMAND_TYPE_TRANS,
        COMMAND_TYPE_INV,
        COMMAND_TYPE_GEM,
        COMMAND_TYPE_DET = 50,
        COMMAND_TYPE_RANK,
        COMMAND_TYPE__END = COMMAND_TYPE_RANK
    };
public:
    CController();

    /**
     * Nastaví view
     * @param m_view
     */
    void setView(CView *m_view);

    /**
     * nastaví model
     * @param m_model
     */
    void setModel(CModel *m_model);

    /**
     * Vykoná příkaz z uživatelského vstupu
     * @param ss příkaz
     */
    void command(std::stringstream& ss);

    /**
     * idetifikuje příkaz
     * @param s příkaz
     * @return typ příkazu
     */
    COMMAND_TYPE identifyCommand(const std::string& s) const;

    /**
     * Zpracovává chyby z uživatelského vstupu a pošle do view daný string
     * @param s
     */
    void wrongCommandHandler(const std::string& s);

    /**
     *
     * Zpracovává chyby z uživatelského vstupu
     * @param s
     */
    void wrongCommandHandler();

    /**
     * Zpracovává příkazy bez návratové hodnoty
     * @param type
     * @param ss
     */
    void commandVoid(COMMAND_TYPE type, std::stringstream& ss);

    /**
     * Zpracovává příkazy s návratovou hodnotou typu double
     * @param type
     * @param ss
     * @return
     */
    double commandDouble(COMMAND_TYPE type, std::stringstream& ss);

    /**
     * Zpracovává příkazy s návratovou hodnotou typu CMatrix
     * @param type
     * @param ss
     * @return
     */
    CMatrix* commandMatrix(COMMAND_TYPE type, std::stringstream& ss);

    /**
     * Zpracovává příkazy orientované na binární operátory
     * @param left
     * @param oper
     * @param ss
     * @return
     */
    CMatrix* commandOperator(CMatrix* left, char oper, std::stringstream& ss);

    /**
     * Zpracovává příkazy orientované na konkrétní prvky v matici
     * @param matrix
     * @param ss
     * @return
     */
    double commandBracket(CMatrix* matrix, std::stringstream& ss);

    /**
     * Metoda pro nastavení všech hodnot v matice dle uživatelského vstupu
     * @param ss
     */
    void commandScan(std::stringstream& ss);

private:
    CView* m_view;
    CModel* m_model;
};


#endif //PA2_SEM_CCONTROLLER_H
