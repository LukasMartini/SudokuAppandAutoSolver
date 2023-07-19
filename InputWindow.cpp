//
// Created by Luke Martin on 2023-03-29.
//

#include "InputWindow.h"
#include <QtWidgets>
#include <QtGui>

#include <fstream>
#include <filesystem>
#include <set>

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

    this->fmbListWidget = new QListWidget(this);
    fmbMainVLayout->addWidget(this->fmbListWidget);
    connect(this->fmbListWidget, &QListWidget::itemDoubleClicked, this, &InputWindow::open);
    this->refreshFileManager();
    auto* fmbOpen = new QPushButton(this);
    fmbOpen->setText(QString {"Open..."});
    fmbButtonHLayout->addWidget(fmbOpen);
    connect(fmbOpen, &QPushButton::pressed, this, &InputWindow::openFromButton);
    auto* fmbDelete = new QPushButton(this);
    fmbDelete->setText(QString ("Delete..."));
    fmbButtonHLayout->addWidget(fmbDelete);
    connect(fmbDelete, &QPushButton::pressed, this, &InputWindow::deleteFile);
    auto* fmbBrowse = new QPushButton(this);
    fmbBrowse->setText(QString {"Browse..."});
    fmbButtonHLayout->addWidget(fmbBrowse);
    connect(fmbBrowse, &QPushButton::pressed, this, &InputWindow::openFileBrowser);

    fmbButtonHContainer->setLayout(fmbButtonHLayout);
    fmbMainVLayout->addWidget(fmbButtonHContainer);
    fmbMainVContainer->setLayout(fmbMainVLayout);

    // ----- Utility Buttons Setup ----- //
    auto* ubLayout = new QVBoxLayout(this);
    auto* ubContainer = new QWidget(this);

    auto* ubModeHContainer = new QWidget(this);
    auto* ubModeHLayout = new QHBoxLayout(this);
    auto* modeLabel = new QLabel(this);
    modeLabel->setText("Mode:");
    ubModeHLayout->addWidget(modeLabel);
    this->modeBar = new QLineEdit(this);
    this->displayTable->getSettingMode() ? this->modeBar->setText(QString ("Set")) : this->modeBar->setText(QString ("Rough"));
    this->modeBar->setEnabled(false);
    ubModeHLayout->addWidget(this->modeBar);
    ubModeHContainer->setLayout(ubModeHLayout);
    ubModeHContainer->setFixedHeight(50);
    ubLayout->addWidget(ubModeHContainer);
    auto* ubCheckSolution = new QPushButton(this);
    ubCheckSolution->setText(QString {"Check Solution"});
    ubLayout->addWidget(ubCheckSolution);
    connect(ubCheckSolution, &QPushButton::pressed, this, &InputWindow::checkIfSolved);
    auto* ubAutoSolve = new QPushButton(this);
    ubAutoSolve->setText(QString {"Auto Solve"});
    ubLayout->addWidget(ubAutoSolve);
    auto* ubSave = new QPushButton(this);
    ubSave->setText(QString {"Save..."});
    connect(ubSave, &QPushButton::pressed, this, &InputWindow::save);
    ubLayout->addWidget(ubSave);
    auto* ubSaveAs = new QPushButton(this);
    ubSaveAs->setText(QString {"Save As..."});
    connect(ubSaveAs, &QPushButton::pressed, this, &InputWindow::saveAs);
    ubLayout->addWidget(ubSaveAs);
    auto* ubNew = new QPushButton(this);
    ubNew->setText(QString {"New..."});
    connect(ubNew, &QPushButton::pressed, this, &InputWindow::newTable);
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
    auto* cmdSaveFile = new QShortcut(QKeySequence(QString("Ctrl+S")), this);
    connect(cmdSaveFile, &QShortcut::activated, this, &InputWindow::save);
    auto* cmdSaveFileAs = new QShortcut(QKeySequence(QString ("Ctrl+Shift+S")), this);
    connect(cmdSaveFileAs, &QShortcut::activated, this, &InputWindow::saveAs);
    auto* cmdOpenFile = new QShortcut(QKeySequence(QString ("Ctrl+O")), this);
    connect(cmdOpenFile, &QShortcut::activated, this, &InputWindow::openFileBrowser);
    auto* cmdNewFile = new QShortcut(QKeySequence(QString ("Ctrl+N")), this);
    connect(cmdNewFile, &QShortcut::activated, this, &InputWindow::newTable);

    // ----- General Setup ----- //
    this->currentFileName = "";
    this->resize(500, 1000);
    this->setWindowTitle(QString {"WFC Sudoku Solver"});
    setCentralWidget(mainContainer);
}


/* ----- Slot Definitions ----- */
void InputWindow::open(QListWidgetItem *filename) {
    // Preconditions:
    // Implementation:
    this->currentFileName = filename->text().toStdString();
    std::ifstream file ("../tables/" + this->currentFileName);
    SudokuTable* newST = new SudokuTable(file, false);
    this->displayTable->setCurrentTable(newST);
    // Postconditions:
    // Return Value:
}

void InputWindow::openFromButton() {
    // Preconditions:
    // Implementation:
    if (this->fmbListWidget->currentItem()) { // This if-statement protects against a crash caused by trying to check for the default item when there are no items in the QListWidget.
        this->open(this->fmbListWidget->currentItem()); // Because of slot jank, I have to do this as a call-from-a-call to be able to connect the button to open since the button has no value to return.
    }
    // Postconditions:
    // Return Value:
}

void InputWindow::openFileBrowser() {
    // Preconditions:
    // Implementation:
    this->currentFileName = QFileDialog::getOpenFileName(this, QString::fromStdString("Open Table"), QString::fromStdString("../tables"), QString::fromStdString("Table Files (*.tbl)")).toStdString();
    this->currentFileName = this->currentFileName.substr(this->currentFileName.find("/tables/") + 8); // The weird substring-ing here is to keep currentFileName consistent. Normally, getOpenFileName will return the full filepath, so I snip out the rest to avoid it causing issues elsewhere.
    std::ifstream file ("../tables/" + this->currentFileName); // NOTE: this is identical to the last section of this->open(), but I'd rather copy/paste than try to macgyver the filename into the list widget. No, thanks.
    SudokuTable* newST = new SudokuTable(file, false);
    this->displayTable->setCurrentTable(newST);
    // Postconditions:
    // Return Value:
}

void InputWindow::deleteFile() {
    // Preconditions:
    // Implementation:
    if (this->fmbListWidget->currentItem()) {
        QMessageBox::StandardButton confirmDeletion = QMessageBox::question(this, "Confirmation", "Are you sure you want to delete " + this->fmbListWidget->currentItem()->text() + "?", QMessageBox::Yes|QMessageBox::No);
        QString *help = new QString ("../tables/" + this->fmbListWidget->currentItem()->text());
        if (confirmDeletion == QMessageBox::Yes) {
            std::filesystem::remove(std::filesystem::path(help->toStdString()));
        }
        this->refreshFileManager();
    }
    // Postconditions:
    // Return Value:
}

void InputWindow::checkIfSolved() {
    // Preconditions:
    // Implementation:
    bool isSolved = true;
    for (int tile = 0; tile < 81; tile++) {
        if (this->displayTable->currentTable->getTile(tile).value >= 1 && this->displayTable->currentTable->getTile(tile).value <= 9) {
            for (auto &section: this->displayTable->currentTable->getTile(tile).adjacencies) {
                std::set<int> currentAdj;
                std::copy(section.begin(), section.end(), std::inserter(currentAdj, currentAdj.end()));
                if (section.size() != currentAdj.size()) {
                    isSolved = false;
                }
            }
        } else {
            isSolved = false;
        }
    }
    if (isSolved) {
        QMessageBox::information(this, "Congratulations!", "Congrats! You've solved the puzzle!", QMessageBox::Ok);
    } else {
        QMessageBox::warning(this, "Uh oh...", "Unfortunately, that's not the correct solution! Try again...", QMessageBox::Ok);
    }
    // Postconditions:
    // Return Value:
}

void InputWindow::save() {
    // Preconditions:
    // Implementation:
    if (this->currentFileName.empty()) {
        this->saveAs();
    } else {
        std::ofstream fileToWriteTo{"../tables/" + this->currentFileName};
        this->displayTable->saveTable(fileToWriteTo);
        fileToWriteTo.close();
        this->refreshFileManager();
    }
    // Postconditions:
    // Return Value:
}

void InputWindow::saveAs() {
    // Preconditions:
    // Implementation:
    bool inputted;
    QString newFileName = QInputDialog::getText(this->tableContainer, QString("New File"), QString("File Name"),QLineEdit::Normal, "", &inputted);
    if (inputted) {
        if (!newFileName.isEmpty() && std::filesystem::exists("../tables/" + newFileName.toStdString() + ".tbl")) {
            QMessageBox::warning(this, "Warning", "Filename already exists. Please choose a new name.",QMessageBox::Ok);
        } else if (newFileName.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Filename cannot be empty.", QMessageBox::Ok);
        } else {
            this->currentFileName = newFileName.toStdString() + ".tbl";
            std::ofstream fileToWriteTo{"../tables/" + this->currentFileName};
            this->displayTable->saveTable(fileToWriteTo);
            fileToWriteTo.close();
            this->refreshFileManager();
        }
    }
    // Postconditions:
    // Return Value:
}

void InputWindow::newTable() {
    // Preconditions:
    // Implementation:
    bool inputted;
    QString newFileName = QInputDialog::getText(this->tableContainer, QString("New File"), QString ("File Name"), QLineEdit::Normal, "", &inputted);
    if (inputted) {
        if (!newFileName.isEmpty() && std::filesystem::exists("../tables/" + newFileName.toStdString() + ".tbl")) {
            QMessageBox::warning(this, "Warning", "Filename already exists. Please choose a new name.",QMessageBox::Ok);
        } else if (newFileName.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Filename cannot be empty.", QMessageBox::Ok);
        } else {
            std::ofstream fileToWriteTo{"../tables/" + newFileName.toStdString() + ".tbl"};
            fileToWriteTo.close();
            this->refreshFileManager();
        }
    }
    // Postconditions:
    // Return Value:
}

void InputWindow::switchMode() {
    this->displayTable->switchMode();
    this->displayTable->getSettingMode() ? this->modeBar->setText(QString ("Set")) : this->modeBar->setText(QString ("Rough"));
}

void InputWindow::refreshFileManager() {
    // Preconditions:
    // Implementation:
    this->fmbListWidget->clear();
    for (auto &it : std::filesystem::directory_iterator("../tables")) {
        if (it.path().filename() != ".gitignore" && it.path().filename().generic_string().substr(it.path().filename().generic_string().length()-4, 4) == ".tbl") {
            auto *filename = new QListWidgetItem();
            filename->setText(QString::fromStdString(it.path().filename()));
            this->fmbListWidget->addItem(filename);
        }
    }
    // Postconditions:
    // Return Value:
}