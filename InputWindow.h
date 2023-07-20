//
// Created by Luke Martin on 2023-03-29.
//
#ifndef WAVECOLLAPSESUDOKUSOLVER_INPUTWINDOW_H
#define WAVECOLLAPSESUDOKUSOLVER_INPUTWINDOW_H

#include "InputTable.h"
//#include "WaveFunctionCollapse.h"

#include <QtWidgets>
#include <QtCore>

class InputWindow : public QMainWindow{
    public:
        InputWindow();
        QWidget* tableContainer;
        // TODO: destructor.

    public slots:
        void open(QListWidgetItem *filename);
        void openFromButton();
        void openFileBrowser();
        void deleteFile();
        void checkIfSolved();
        bool returnSolved();
        SudokuTable* autosolver();
        void save();
        void saveAs();
        void newTable();
        void setValue();

        void switchMode();
        void refreshFileManager();

    private:
        std::string currentFileName;
        InputTable* displayTable;
        QListWidget* fmbListWidget;

        QLineEdit* modeBar;
};


#endif