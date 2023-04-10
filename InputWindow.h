//
// Created by Luke Martin on 2023-03-29.
//
#ifndef WAVECOLLAPSESUDOKUSOLVER_INPUTWINDOW_H
#define WAVECOLLAPSESUDOKUSOLVER_INPUTWINDOW_H

#include "InputTable.h"

#include <map>
#include <vector>

#include <QtWidgets>

class InputWindow : public QMainWindow{
    public:
        InputWindow();
        QWidget* tableContainer;
        // TODO: destructor.

    public slots:
        SudokuTable open(std::ifstream &file);
        bool checkIfSolved();
        SudokuTable autosolver();
        void save() const;
        void saveAs();
        void newTable();

    private:
        std::string currentFileName;
        InputTable* displayTable;
};


#endif