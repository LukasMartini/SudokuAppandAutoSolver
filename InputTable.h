//
// Created by Luke Martin on 2023-04-06.
//

#include "SudokuTable.h"

#include <map>
#include <vector>

#include <QtWidgets>

#ifndef WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H
#define WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H


// ON THE DIFFERENCE BETWEEN InputTable AND SudokuTable:
// InputTable is the grid that the user interfaces with, SudokuTable is the data structure used to handle storage and loading.

class InputTable : public QWidget{
    public:
        InputTable();
        QGridLayout* tableLayout;
        // TODO: destructor.

        void saveTable(std::ofstream &file);

        std::map<int, int> getInputTableValues() const;
        bool getSettingMode() const;

        void setCurrentTable(SudokuTable* newTable);

    public slots:
        int returnUpdatedTileValue(const QString&);
        void switchMode();

    private:
        SudokuTable* currentTable;
        std::map<int, QLineEdit*> tileInputBoxes;

        bool validateLength(const QString& values) const;
        static int validateNoDuplicates(const std::string &values);

        std::string makePrintableVector(std::vector<int> target);
        std::string makePrintableVectorOfVectors(std::vector<std::vector<int>> target);

        const QRegularExpression settingRE {"^[1-9]{0,1}$"};
        const QString settingSS {"border : 2px solid black;"
                               "background : white;"
                               "height : 50px;"
                               "width : 50px;"
                               "color : black;"
                               "font-size : 20px"};
        const QRegularExpression possibilitiesRE {"^[1-9]{0,10}$"};
        const QString possibilitiesSS { "border : 2px solid black;"
                                  "background : white;"
                                  "height : 50px;"
                                  "width : 50px;"
                                  "color : black;"
                                  "font-size : 10px"};
        const QValidator* forceTheseValuesWhenSetting = new QRegularExpressionValidator(settingRE, this);
        const QValidator* forceTheseValuesWhenPossibilitying = new QRegularExpressionValidator(possibilitiesRE, this);
        bool settingMode = true; // inputMode being true means set number mode, false means possibilities mode.
};


#endif //WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H