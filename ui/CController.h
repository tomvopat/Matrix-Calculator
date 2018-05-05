//
// Created by Tomáš Vopat on 05.05.18.
//

#ifndef PA2_SEM_CCONTROLLER_H
#define PA2_SEM_CCONTROLLER_H

#include <string>

class CView;
class CModel;

class CController {
public:
    CController();

    void setView(CView *m_view);
    void setModel(CModel *m_model);

    void command(const std::string& s);
private:
    CView* m_view;
    CModel* m_model;

    enum COMMAND_TYPE {
        COMMAND_TYPE__BEGIN = 0,
        COMMAND_TYPE_DECLARE = COMMAND_TYPE__BEGIN,
        COMMAND_TYPE_SET_VALUE,
        COMMAND_TYPE_SCAN,
        COMMAND_TYPE_ASSIGN,
        COMMAND_TYPE_MERGE,
        COMMAND_TYPE_CUT,
        COMMAND_TYPE_DET,
        COMMAND_TYPE_RANK,
        COMMAND_TYPE_TRANS,
        COMMAND_TYPE_INV,
        COMMAND_TYPE_GEM,
        COMMAND_TYPE__END = COMMAND_TYPE_GEM
    };
};


#endif //PA2_SEM_CCONTROLLER_H
