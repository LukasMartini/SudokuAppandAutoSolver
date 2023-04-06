//
// Created by Luke Martin on 2023-03-29.
//
#include "SudokuTable.h"

#include <map>
#include <vector>

#include <QtWidgets>

class InputTable : public QWidget{
public:
    InputTable();
    QGridLayout* tableLayout;

//    void updateScreen(const std::map<int, int> &changedValues);

public slots:
    int returnUpdatedTileValue(QString);

private:
    SudokuTable currentTable;
    std::map<int, QLineEdit*> tileInputBoxes;
};

class InputWindow : public QMainWindow{
    public:
        InputWindow();
        QWidget* tableContainer;

    private:
        SudokuTable open(std::ifstream &file);
        bool checkIfSolved();
        SudokuTable autosolver();
        void save();
        void saveAs();
        void newTable();

        SudokuTable table;
        std::string currentFileName;
        QVBoxLayout* mainLayout;
        QWidget* mainContainer;
        InputTable* displayTable;
};
