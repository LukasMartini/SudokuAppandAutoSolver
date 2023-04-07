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

    private:
        SudokuTable open(std::ifstream &file);
        bool checkIfSolved();
        SudokuTable autosolver();
        void save();
        void saveAs();
        void newTable();

        std::string currentFileName;
        InputTable* displayTable;
};


#endif