//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CCONTROLLER_H
#define PA2_SEM_CCONTROLLER_H

#include <string>

class CView;
class CModel;
class CMatrix;

class CController {
private:
    enum COMMAND_TYPE {
        COMMAND_TYPE__BEGIN = 0,
        COMMAND_TYPE_EXIT = COMMAND_TYPE__BEGIN,
        COMMAND_TYPE_VAR,
        COMMAND_TYPE_LIST,
        COMMAND_TYPE_PRINT,
        COMMAND_TYPE_MATRIX = 10,
        COMMAND_TYPE_ID,
        COMMAND_TYPE_SCAN,
        COMMAND_TYPE_MERGE,
        COMMAND_TYPE_CUT,
        COMMAND_TYPE_TRANS,
        COMMAND_TYPE_INV,
        COMMAND_TYPE_GEM,
        COMMAND_TYPE_DET = 20,
        COMMAND_TYPE_RANK,
        COMMAND_TYPE_DOUBLE,
        COMMAND_TYPE__END = COMMAND_TYPE_DOUBLE
    };
public:
    CController();

    void setView(CView *m_view);
    void setModel(CModel *m_model);

    void command(std::stringstream& ss);
    COMMAND_TYPE identifyCommand(const std::string& s) const;
    void unknownCommandHandler();
    void wrongCommandHandler(const std::string& s);

    void commandVoid(COMMAND_TYPE type, std::stringstream& ss);
    double commandDouble(COMMAND_TYPE type, std::stringstream& ss);
    CMatrix* commandMatrix(COMMAND_TYPE type, std::stringstream& ss);

private:
    CView* m_view;
    CModel* m_model;
};


#endif //PA2_SEM_CCONTROLLER_H
