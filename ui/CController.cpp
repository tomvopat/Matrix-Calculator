//
// Created by Tomáš Vopat on 05.05.18.
//


#include <sstream>
#include <iostream>
#include <matrix/CMatrix.h>
#include <tools/CInvalidMatrixException.h>
#include <matrix/CMatrixFull.h>
#include <matrix/CMatrixSparse.h>
#include "CController.h"
#include "CView.h"
#include "CModel.h"
#include "../tools/CMVCException.h"

/*
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
        COMMAND_TYPE__END = COMMAND_TYPE_RANK
    */

CController::CController() : m_view(NULL), m_model(NULL) {}

void CController::setView(CView *m_view) {
    CController::m_view = m_view;
}

void CController::setModel(CModel *m_model) {
    CController::m_model = m_model;
}

void CController::command(std::stringstream& ss) {
    if(!m_view || !m_model) throw CMVCException("Chybí view nebo model.");

    if(ss.eof()) return;

    std::string part;
    ss >> part;
    COMMAND_TYPE type = identifyCommand(part);
    if(type == COMMAND_TYPE_ID) {
        char c;
        ss >> c;
        if(c == '(') {
            try{
                double result = commandDouble(type, ss);
                m_view->show("Value: " + std::to_string(result));
            } catch(CMVCException ex) {
                //todo
                wrongCommandHandler(ex.getM_message());
            }
        }
        else if(c == '=') {
            try {
                CMatrix* result = commandMatrix(type, ss);
                m_model->remove(part);
                m_model->add(part, result);
                delete result;
            } catch (CMVCException ex) {
                //todo
                wrongCommandHandler(ex.getM_message());
            }

        }
        else {
            //todo
            unknownCommandHandler();
        }
    }
    else {
        if(type < 10) {
            try {
                commandVoid(type, ss);
            } catch (CMVCException ex) {
                //todo
                wrongCommandHandler(ex.getM_message());
            }
            return;
        }
        if(type < 20) {
            try {
                CMatrix* result = commandMatrix(type, ss);
                m_model->setTmp(result);
                delete result;
                m_view->showTmpFromModel();
            } catch(CMVCException ex) {
                //todo
                wrongCommandHandler(ex.getM_message());
            }
        }
        else {
            try{
                double result = commandDouble(type, ss);
                m_view->show("Result: " + std::to_string(result));
            } catch(CMVCException ex) {
                //todo
                wrongCommandHandler(ex.getM_message());
            }
        }
    }
}

CController::COMMAND_TYPE CController::identifyCommand(const std::string& s) const {
    if(s.compare("EXIT") == 0) return COMMAND_TYPE_EXIT;
    if(s.compare("VAR") == 0) return COMMAND_TYPE_VAR;
    if(s.compare("MATRIX") == 0) return COMMAND_TYPE_MATRIX;
    if(s.compare("SCAN") == 0) return COMMAND_TYPE_SCAN;
    if(s.compare("MERGE") == 0) return COMMAND_TYPE_MERGE;
    if(s.compare("CUT") == 0) return COMMAND_TYPE_CUT;
    if(s.compare("DET") == 0) return COMMAND_TYPE_DET;
    if(s.compare("RANK") == 0) return COMMAND_TYPE_RANK;
    if(s.compare("TRANS") == 0) return COMMAND_TYPE_TRANS;
    if(s.compare("INV") == 0) return COMMAND_TYPE_INV;
    if(s.compare("GEM") == 0) return COMMAND_TYPE_GEM;
    if(s.compare("LIST") == 0) return COMMAND_TYPE_LIST;
    if(s.compare("PRINT") == 0) return COMMAND_TYPE_PRINT;
    return COMMAND_TYPE_ID;
}

void CController::unknownCommandHandler() {
    m_view->show("--- Error ---");
}

void CController::wrongCommandHandler(const std::string &s) {
    m_view->show(s);
}

void CController::commandVoid(CController::COMMAND_TYPE type, std::stringstream& ss) {
    switch(type) {
        case COMMAND_TYPE_PRINT:
            {
                std::string id;
                ss >> id;
                if(! m_model->contains(id)) wrongCommandHandler("Wrong identifier.");
                m_view->showFromModel(id);
            }
            break;
        case COMMAND_TYPE_EXIT:
            m_view->stop();
            break;
        default:
            throw CMVCException("??? ERROR ???");
    }
}

double CController::commandDouble(CController::COMMAND_TYPE type, std::stringstream& ss) {
    switch(type) {
        case COMMAND_TYPE_ID:
            break;
        case COMMAND_TYPE_DET:
            {
                std::string id;
                ss >> id;
                if (!m_model->contains(id)) throw CMVCException("Wrong identifier.");
                CMatrix *matrix = m_model->get(id);
                double result = matrix->getDeterminant();
                delete matrix;
                return result;
            }
        case COMMAND_TYPE_RANK:
            {
                std::string id;
                ss >> id;
                if (!m_model->contains(id)) throw CMVCException("Wrong identifier.");
                CMatrix *matrix = m_model->get(id);
                double result = matrix->getRank();
                delete matrix;
                return result;
            }
        default:
            throw CMVCException("??? ERROR ???");
    }
}

CMatrix *CController::commandMatrix(CController::COMMAND_TYPE type, std::stringstream& ss) {
    switch(type) {
        case COMMAND_TYPE_MATRIX:
            {
                std::string matrixType;
                ss >> matrixType;
                if((matrixType != "-F") && (matrixType != "-S")) {
                    throw CMVCException("wrong syntax.");
                }
                char a,b,c;
                int i,j;
                ss >> a >> i >> b >> j >> c;
                if((a != '[') || (b != ',') || (c != ']')) {
                    throw CMVCException("wrong syntax.");
                }
                if(matrixType == "-F") {
                    return new CMatrixFull(i,j);
                }
                else {
                    return new CMatrixSparse(i,j);
                }
            }
            break;
        case COMMAND_TYPE_ID:
            break;
        case COMMAND_TYPE_SCAN:
            break;
        case COMMAND_TYPE_MERGE:
            break;
        case COMMAND_TYPE_CUT:
            break;
        case COMMAND_TYPE_TRANS:
            break;
        case COMMAND_TYPE_INV:
            break;
        case COMMAND_TYPE_GEM:
            break;
        default:
            throw CMVCException("??? ERROR ???");
    }
}
