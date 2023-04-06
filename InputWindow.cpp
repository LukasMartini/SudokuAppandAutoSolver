//
// Created by Luke Martin on 2023-03-29.
//

#include "InputWindow.h"
#include <QtWidgets>

#include <iostream>


// ----- InputWindow DEFINITIONS ----- //
InputWindow::InputWindow() {
    this->currentFileName = "";
    this->displayTable = new InputTable;
    this->tableContainer = new QWidget;

    this->mainLayout = new QVBoxLayout;
    this->mainContainer = new QWidget;

    this->tableContainer->setLayout(this->displayTable->tableLayout);
    this->tableContainer->setMaximumSize(500, 500);
    this->tableContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    this->resize(600, 1000);
    this->setWindowTitle(QString {"WFC Sudoku Solver"});
    setCentralWidget(this->tableContainer);

    this->tableContainer->show();
}


// ----- InputTable DEFINITIONS ----- //
InputTable::InputTable() {
    this->tableLayout = new QGridLayout;
    for (int i = 0; i < 81; i++) {
        QLineEdit* newBox = new QLineEdit;
        newBox->setStyleSheet({
            "border : 2px solid black;"
            "background : white;"
            "height : 50px;"
            "color : black"
        });
        connect(newBox, &QLineEdit::textChanged, this, &InputTable::returnUpdatedTileValue);
        this->tileInputBoxes[i] = newBox;
        this->tableLayout->addWidget(newBox, i - (i % 9), i % 9, 1, 1);
    }
    this->tableLayout->setSpacing(0);
    this->tableLayout->setContentsMargins(0,0,0,0);
}

int InputTable::returnUpdatedTileValue(QString newVal) {
    std::cout << newVal.toStdString() << std::endl;
}