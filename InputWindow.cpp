//
// Created by Luke Martin on 2023-03-29.
//

#include "InputWindow.h"
#include <QtWidgets>
#include <QtGui>

#include <fstream>
#include <filesystem>

#include <iostream>


// ----- InputWindow DEFINITIONS ----- //
InputWindow::InputWindow() {

    // ----- DEVELOPMENT TEMPORARY STUFF ----- //
    this->currentFileName = "temp.txt";

    // ----- Sudoku Table Setup ----- //
    this->displayTable = new InputTable;
    this->tableContainer = new QWidget;
    this->tableContainer->setLayout(this->displayTable->tableLayout);
    this->tableContainer->setMaximumSize(500, 500);
    this->tableContainer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // ----- File Management Buttons Setup ----- //
    auto* fmbMainVLayout = new QVBoxLayout(this);
    auto* fmbMainVContainer = new QWidget(this);
    auto* fmbButtonHLayout = new QHBoxLayout(this);
    auto* fmbButtonHContainer = new QWidget(this);

    auto* fmbListWidget = new QListWidget(this);
    fmbMainVLayout->addWidget(fmbListWidget);
    connect(fmbListWidget, &QListWidget::itemDoubleClicked, this, &InputWindow::open);
    for (auto &it : std::filesystem::directory_iterator("../tables")) {
        auto* filename = new QListWidgetItem();
        filename->setText(QString::fromStdString(it.path().filename()));
        fmbListWidget->addItem(filename);
    }
    auto* fmbOpen = new QPushButton(this);
    fmbOpen->setText(QString {"Open..."});
    fmbButtonHLayout->addWidget(fmbOpen);
    auto* fmbBrowse = new QPushButton(this);
    fmbBrowse->setText(QString {"Browse..."});
    fmbButtonHLayout->addWidget(fmbBrowse);

    fmbButtonHContainer->setLayout(fmbButtonHLayout);
    fmbMainVLayout->addWidget(fmbButtonHContainer);
    fmbMainVContainer->setLayout(fmbMainVLayout);

    // ----- Utility Buttons Setup ----- //
    auto* ubLayout = new QVBoxLayout(this);
    auto* ubContainer = new QWidget(this);

    this->modeBar = new QLineEdit(this);
    this->modeBar->setText(QString {QVariant(this->displayTable->getSettingMode()).toString()});
    ubLayout->addWidget(this->modeBar);
    auto* ubCheckSolution = new QPushButton(this);
    ubCheckSolution->setText(QString {"Check Solution"});
    ubLayout->addWidget(ubCheckSolution);
    auto* ubAutoSolve = new QPushButton(this);
    ubAutoSolve->setText(QString {"Auto Solve"});
    ubLayout->addWidget(ubAutoSolve);
    auto* ubSave = new QPushButton(this);
    ubSave->setText(QString {"Save..."});
    connect(ubSave, &QPushButton::pressed, this, &InputWindow::save);
    ubLayout->addWidget(ubSave);
    auto* ubSaveAs = new QPushButton(this);
    ubSaveAs->setText(QString {"Save As..."});
    ubLayout->addWidget(ubSaveAs);
    auto* ubNew = new QPushButton(this);
    ubNew->setText(QString {"New..."});
    ubLayout->addWidget(ubNew);

    ubContainer->setLayout(ubLayout);


    // ----- Additional Interface Setup ----- //
    auto* AILayout = new QHBoxLayout(this);
    auto* AIContainer = new QWidget(this);

    AILayout->addWidget(fmbMainVContainer);
    AILayout->addWidget(ubContainer);

    AIContainer->setLayout(AILayout);

    // ----- Main Layout Setup ----- //
    auto* mainLayout = new QVBoxLayout(this);
    auto* mainContainer = new QWidget(this);

    mainLayout->addWidget(this->tableContainer);
    mainLayout->addWidget(AIContainer);

    mainContainer->setLayout(mainLayout);

    // ----- Keyboard Shortcuts Setup ----- //
    auto* cmdSwitchInputMode = new QShortcut(QKeySequence (QString ("Ctrl+,")), this);
    connect(cmdSwitchInputMode, &QShortcut::activated, this, &InputWindow::switchMode);
    auto* cmdRefreshFileManager = new QShortcut(QKeySequence(QString ("Ctrl+R")), this);
    connect(cmdRefreshFileManager, &QShortcut::activated, this, &InputWindow::refreshFileManager);

    // ----- General Setup ----- //
    this->currentFileName = "";
    this->resize(500, 1000);
    this->setWindowTitle(QString {"WFC Sudoku Solver"});
    setCentralWidget(mainContainer);
}


/* ----- Slot Definitions ----- */
void InputWindow::open(QListWidgetItem *filename) {
    //TODO: Implement.
    // Preconditions:
    // Implementation:
    std::ifstream file ("../tables/" + filename->text().toStdString());
    SudokuTable* newST = new SudokuTable(file, false); // TODO: decide as to how to deal with this. Probably include isSet in the file, get ready to refactor lmao.
    this->displayTable->setCurrentTable(newST);
    // Postconditions:
    // Return Value:
}

void InputWindow::save() const{
    // Preconditions:
    // Implementation:
    std::ofstream fileToWriteTo {"../tables/temp.txt"}; // TODO: generalize this to this->currentFileName when done implementing
    this->displayTable->saveTable(fileToWriteTo);
    // Postconditions:
    // Return Value:
}

void InputWindow::switchMode() {
    this->displayTable->switchMode();
    this->modeBar->setText(QString {QVariant(this->displayTable->getSettingMode()).toString()});
}

void InputWindow::refreshFileManager() {

}