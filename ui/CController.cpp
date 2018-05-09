//
// Created by Tomáš Vopat on 05.05.18.
//


#include <sstream>
#include <iostream>
#include <fstream>
#include <iomanip>
#include "CController.h"
#include "CView.h"
#include "CModel.h"
#include "../tools/CMVCException.h"
#include "../tools/Numbers.h"
#include "../tools/CInvalidMatrixException.h"
#include "../matrix/CMatrixFull.h"
#include "../matrix/CMatrixSparse.h"

CController::CController() : m_view(NULL), m_model(NULL) {}

void CController::setView(CView *m_view) {
    CController::m_view = m_view;
}

void CController::setModel(CModel *m_model) {
    CController::m_model = m_model;
}

CController::COMMAND_TYPE CController::identifyCommand(const std::string& s) const {
    if(Numbers::isDouble(s)) return COMMAND_TYPE_DOUBLE;
    if((s.compare("+") == 0) || (s.compare("-") == 0) || (s.compare("*") == 0)) return COMMAND_TYPE_OPERATOR;
    if(s.compare("(") == 0) return COMMAND_TYPE_BRACKET;
    if(s.compare("=") == 0) return COMMAND_TYPE_EQUATOR;
    if(s.compare("MATRIX") == 0) return COMMAND_TYPE_MATRIX;
    if(s.compare("SCAN") == 0) return COMMAND_TYPE_SCAN;
    if(s.compare("MERGE") == 0) return COMMAND_TYPE_MERGE;
    if(s.compare("CUT") == 0) return COMMAND_TYPE_CUT;
    if(s.compare("TRANS") == 0) return COMMAND_TYPE_TRANS;
    if(s.compare("INV") == 0) return COMMAND_TYPE_INV;
    if(s.compare("GEM") == 0) return COMMAND_TYPE_GEM;
    if(s.compare("LIST") == 0) return COMMAND_TYPE_LIST;
    if(s.compare("DET") == 0) return COMMAND_TYPE_DET;
    if(s.compare("RANK") == 0) return COMMAND_TYPE_RANK;
    if(s.compare("EXIT") == 0) return COMMAND_TYPE_EXIT;
    if(s.compare("PRINT") == 0) return COMMAND_TYPE_PRINT;
    if(s.compare("HELP") == 0) return COMMAND_TYPE_HELP;
    return COMMAND_TYPE_ID;
}

void CController::wrongCommandHandler() {
    m_view->show("--- Error ---");
}

void CController::wrongCommandHandler(const std::string &s) {
    m_view->show(s);
}

void CController::command(std::stringstream& ss) {
    if(!m_view || !m_model) throw CMVCException("Chybí view nebo model.");

    std::string input;
    ss >> input;

    if(ss.eof() && input.empty()) return;

    COMMAND_TYPE type = identifyCommand(input);
    if(type == COMMAND_TYPE_ID) {
        // A, B, C, ...
        char subInput;
        ss >> subInput;
        COMMAND_TYPE subType = identifyCommand(std::string(1, subInput));
        if(subType == COMMAND_TYPE_OPERATOR) {
            // A +/-/* B
            if(! m_model->contains(input)) {
                wrongCommandHandler("Matrix not found.");
                return;
            }
            CMatrix* matrixA = m_model->get(input);
            CMatrix* result = NULL;
            try {
                result = commandOperator(matrixA, subInput, ss);
            } catch (CMVCException ex) {
                delete matrixA;
                wrongCommandHandler(ex.getM_message());
                return;
            }
            delete matrixA;
            m_model->setTmp(result);
            delete result;
            m_view->showTmpFromModel();
            return;
        }
        else if(subType == COMMAND_TYPE_BRACKET) {
            // A (k,l)
            if(! m_model->contains(input)) throw CMVCException("Matrix not found.");
            CMatrix* matrixA = m_model->get(input);
            double result;
            try {
                result = commandBracket(matrixA, ss);
            } catch (CMVCException ex) {
                wrongCommandHandler(ex.getM_message());
                return;
            }
            m_model->remove(input);
            m_model->add(input, matrixA);
            delete matrixA;
            std::stringstream sss;
            sss << std::fixed << std::setw(10) << std::setprecision(2) << result;
            m_view->show("result: " + sss.str());
            return;
        }
        else if(subType == COMMAND_TYPE_EQUATOR) {
            // A = ...
            if(m_model->contains(input)) m_model->remove(input);
            CMatrix* result = NULL;
            try {
                result = commandMatrix(subType, ss);
            } catch (CMVCException ex) {
                wrongCommandHandler(ex.getM_message());
                return;
            }
            m_model->add(input, result);
            delete result;
            return;
        }
        else {}
        wrongCommandHandler("Unknown command.");
    }
    else if(type < 10) {
        //EXIT, LIST, PRINT A
        commandVoid(type, ss);
        return;
    }
    else if(type == COMMAND_TYPE_SCAN) {
        try {
            commandScan(ss);
        } catch (CMVCException ex) {
            wrongCommandHandler(ex.getM_message());
            return;
        }
        return;
    }
    else if((type >= 30) && (type < 50)) {
        //MATRIX, MERGE, CUT
        CMatrix* result = NULL;
        try {
            result = commandMatrix(type, ss);
        } catch (CMVCException ex) {
            wrongCommandHandler(ex.getM_message());
            return;
        }
        m_model->setTmp(result);
        delete result;
        m_view->showTmpFromModel();
        return;
    }
    else if(type >= 50) {
        // DET, RANK
        double result = 0;
        try {
            result = commandDouble(type, ss);
        } catch(CInvalidMatrixException ex) {
            wrongCommandHandler("Invalid operation for this matrix.");
            return;
        }
        std::stringstream sss;
        sss << std::fixed << std::setw(10) << std::setprecision(2) << result;
        m_view->show("result: " + sss.str());
        return;
    }
    else {
        wrongCommandHandler("Wrong command.");
        return;
    }
//    else throw CMVCException("??? ERROR ???");
}

void CController::commandVoid(CController::COMMAND_TYPE type, std::stringstream& ss) {
    switch(type) {
        case COMMAND_TYPE_PRINT:
        {
            std::string id;
            ss >> id;
            if(! m_model->contains(id)) wrongCommandHandler("Matrix not found.");
            m_view->showFromModel(id);
            return;
        }
        case COMMAND_TYPE_EXIT:
        {
            m_view->show("Stopping . . .");
            m_view->stop();
            return;
        }
        case COMMAND_TYPE_LIST:
        {
            m_view->showAllFromModel();
            return;
        }
        case COMMAND_TYPE_HELP:
        {
            std::ifstream inFile;
            inFile.open("src/ui/help.txt");
            std::string line;
            if(! inFile.is_open()) throw CMVCException("Help not found.");
            while(getline(inFile, line)) m_view->show(line);
            inFile.close();
            return;
        }
        default:
            throw CMVCException("ERROR");
    }
}

double CController::commandDouble(CController::COMMAND_TYPE type, std::stringstream& ss) {
    switch(type) {
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
        case COMMAND_TYPE_EQUATOR:
        {
            std::string input;
            ss >> input;
            COMMAND_TYPE subType = identifyCommand(input);
            if(subType == COMMAND_TYPE_DOUBLE) {
                return std::stod(input);
            }
            else {
                return commandDouble(subType, ss);
            }
        }
        default:
            throw CMVCException("ERROR");
    }
}

CMatrix *CController::commandMatrix(CController::COMMAND_TYPE type, std::stringstream& ss) {
    switch(type) {
        //ok
        case COMMAND_TYPE_MATRIX:
        {
            std::string matrixType;
            ss >> matrixType;
            if((matrixType != "-F") && (matrixType != "-S")) {
                throw CMVCException("wrong switch.");
            }
            char a,b,c,d;
            int i,j;
            ss >> a >> i >> b >> j >> c >> d;
            if(!ss.eof()) throw CMVCException("Wrong syntax.");
            if((a != '[') || (b != ',') || (c != ']')) {
                throw CMVCException("wrong syntax.");
            }
            if(matrixType == "-F") {
                try {
                    return new CMatrixFull(i,j);
                } catch (CInvalidMatrixException ex) {
                    throw CMVCException("Wrong size of the full matrix.");
                }
            }
            else {
                try {
                    return new CMatrixSparse(i,j);
                } catch (CInvalidMatrixException ex) {
                    throw CMVCException("Wrong size of the sparse matrix.");
                }
            }
        }
        case COMMAND_TYPE_EQUATOR:
        {
            std::string input;
            ss >> input;
            COMMAND_TYPE subType = identifyCommand(input);
            if(subType == COMMAND_TYPE_ID) {
                if(! m_model->contains(input)) throw CMVCException("Matrix not found.");
                CMatrix* matrixA = m_model->get(input);
                char c;
                ss >> c;
                if(ss.eof()) return matrixA;
                if((c != '+') && (c != '-') && (c != '*')) throw CMVCException("Invalid syntax.");
                CMatrix* result = commandOperator(matrixA, c, ss);
                delete matrixA;
                return result;
            }
            else {
                return commandMatrix(subType, ss);
            }
        }
        case COMMAND_TYPE_MERGE:
        {
            std::string matrixType;
            ss >> matrixType;
            if((matrixType != "-H") && (matrixType != "-V")) {
                throw CMVCException("wrong switch.");
            }

            std::string matrixA, matrixB, rest;
            ss >> matrixA >> matrixB >> rest;
            if(! ss.eof()) throw CMVCException("Wrong syntax.");
            if((! m_model->contains(matrixA)) || (! m_model->contains(matrixB))) {
                throw CMVCException("wrong indetifiers.");
            }

            CMatrix *a, *b, *result;
            a = m_model->get(matrixA);
            b = m_model->get(matrixB);
            if(matrixType == "-H") result = a->merge(*b, true);
            else result = a->merge(*b, false);
            delete a;
            delete b;
            return result;
        }
        case COMMAND_TYPE_CUT:
        {
            std::string matrixA;
            ss >> matrixA;
            if(! m_model->contains(matrixA)) throw CMVCException("wrong indetifier.");

            char a,b,c,d,e,f;
            int i,j,k,l;
            std::string rest;
            ss >> a >> i >> b >> j >> c >> d >> k >> e >> l >> f >> rest;
            if(! ss.eof()) throw CMVCException("Wrong syntax.");
            if((a != '(') || (b != ',') || (c != ')') || (d != '(') || (e != ',') || (f != ')')) {
                throw CMVCException("Wrong syntax.");
            }
            CMatrix *aM, *result;
            aM = m_model->get(matrixA);
            result = aM->cut(CPoint_2D(j, i), CPoint_2D(l,k));
            delete aM;
            return result;
        }
        case COMMAND_TYPE_TRANS:
        {
            std::string id, rest;
            ss >> id >> rest;
            if(! ss.eof()) throw CMVCException("Wrong syntax.");
            if (!m_model->contains(id)) throw CMVCException("Wrong identifier.");
            CMatrix *a, *result;
            a = m_model->get(id);
            result = a->getTransposed();
            delete a;
            return result;
        }
        case COMMAND_TYPE_INV:
        {
            std::string id, rest;
            ss >> id >> rest;
            if(! ss.eof()) throw CMVCException("Wrong syntax.");
            if (!m_model->contains(id)) throw CMVCException("Wrong identifier.");
            CMatrix* a, *result;
            a = m_model->get(id);
            try {
                result = a->getInverse();
            } catch (CInvalidMatrixException ex) {
                delete a;
                throw CMVCException("Only for square matrices.");
            }
            delete a;
            return result;
        }
        case COMMAND_TYPE_GEM:
        {
            std::string id, rest;
            ss >> id >> rest;
            if(! ss.eof()) throw CMVCException("Wrong syntax.");
            if (!m_model->contains(id)) throw CMVCException("Wrong identifier.");
            CMatrix* a, *result;
            a = m_model->get(id);
            result = a->gem();
            delete a;
            return result;
        }
        default:
            throw CMVCException("ERROR");
    }
}

CMatrix *CController::commandOperator(CMatrix *left, char oper, std::stringstream &ss) {
    std::string input;
    ss >> input;
    if(! m_model->contains(input)) throw CMVCException("Matrix not found.");
    CMatrix* matrixB = m_model->get(input);
    CMatrix* result = NULL;
    if(oper == '+') {
        try {
            result = *left + *matrixB;
        } catch (CInvalidMatrixException ex) {
            delete matrixB;
            throw CMVCException("Wrong matrices.");
        }
    }
    else if(oper == '-') {
        try {
            result = *left - *matrixB;
        } catch (CInvalidMatrixException ex) {
            delete matrixB;
            throw CMVCException("Wrong matrices.");
        }
    }
    else if(oper == '*') {
        try {
            result = *left * *matrixB;
        } catch (CInvalidMatrixException ex) {
            delete matrixB;
            throw CMVCException("Wrong matrices.");
        }
    }
    else {
        delete matrixB;
        throw CMVCException("Invalid operator.");
    }

    delete matrixB;
    return result;
}

double CController::commandBracket(CMatrix *matrix, std::stringstream &ss) {
    int k,l;
    char a,b,c;
    ss >> k >> a >> l >> b >> c;
    if((a != ',') || (b != ')')) throw CMVCException("Wrong syntax.");
    if(! matrix->isValid(CPoint_2D(l, k))) throw CMVCException("Invalid indices.");

    if(ss.eof()) {
        return matrix->getValue(CPoint_2D(l, k));
    }
    else {
        if(c != '=') throw CMVCException("Wrong syntax.");
        double result = commandDouble(COMMAND_TYPE_EQUATOR, ss);
        matrix->setValue(result, CPoint_2D(l,k));
        return result;
    }
}

void CController::commandScan(std::stringstream &ss) {
    std::string id;
    ss >> id;
    if(! m_model->contains(id)) throw CMVCException("Invalid identifier");
    CMatrix* matrix = m_model->get(id);
    int i = 0,j = 0, in;
    int count = 0;
    while(std::cin >> std::skipws >> in) {
        if(i >= matrix->getWidth()) {
            i = 0;
            j++;
        }
        if(j >= matrix->getHeight()) {
            delete matrix;
            throw CMVCException("SCAN failed.");
        }
        matrix->setValue(in, CPoint_2D(i++,j));
        count++;
        if(count == (matrix->getWidth() * matrix->getHeight())) break;
    }
    if(count != (matrix->getWidth() * matrix->getHeight())) {
        delete matrix;
        throw CMVCException("SCAN failed.");
    }
    m_model->remove(id);
    m_model->add(id, matrix);
    delete matrix;
}
