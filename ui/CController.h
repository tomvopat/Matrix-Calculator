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
 * Class for representation controller in MVC
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
    void setView(CView *m_view);
    void setModel(CModel *m_model);

    /**
     * Executes command from UI
     * @param ss command
     */
    void command(std::stringstream& ss);

    /**
     * method for command identification
     * @param s command
     * @return typ command type
     */
    COMMAND_TYPE identifyCommand(const std::string& s) const;

    /**
     * Process error from UI. Sends errors to view
     * @param s
     */
    void wrongCommandHandler(const std::string& s);

    /**
     * Process error form UI
     * @param s
     */
    void wrongCommandHandler();

    /**
     * Proccess commands without return value
     * @param type
     * @param ss
     */
    void commandVoid(COMMAND_TYPE type, std::stringstream& ss);

    /**
     * Process commands with return value of type double
     * @param type
     * @param ss
     * @return
     */
    double commandDouble(COMMAND_TYPE type, std::stringstream& ss);

    /**
     * Process commands with return value of type CMatrix
     * @param type
     * @param ss
     * @return
     */
    CMatrix* commandMatrix(COMMAND_TYPE type, std::stringstream& ss);

    /**
     * Process commands oriented to binary operators
     * @param left
     * @param oper
     * @param ss
     * @return
     */
    CMatrix* commandOperator(CMatrix* left, char oper, std::stringstream& ss);

    /**
     * Process command oriented to exact values in matrix
     * @param matrix
     * @param ss
     * @return
     */
    double commandBracket(CMatrix* matrix, std::stringstream& ss);

    /**
     * Method for setting all values in matrix
     * @param ss
     */
    void commandScan(std::stringstream& ss);

private:
    CView* m_view;
    CModel* m_model;
};


#endif //PA2_SEM_CCONTROLLER_H
