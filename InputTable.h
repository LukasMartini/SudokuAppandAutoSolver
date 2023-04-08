//
// Created by Luke Martin on 2023-04-06.
//

#include "SudokuTable.h"

#include <map>
#include <vector>

#include <QtWidgets>

#ifndef WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H
#define WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H


class InputTable : public QWidget{
    public:
        InputTable();
        QGridLayout* tableLayout;
        // TODO: destructor.

    //    void updateScreen(const std::map<int, int> &changedValues);

    public slots:
        int returnUpdatedTileValue(QString);
        void switchMode();

    private:
        bool validateLength(QString values);
        bool validateNoDuplicates(std::string values);

        SudokuTable currentTable;
        std::map<int, QLineEdit*> tileInputBoxes;
        QRegularExpression settingRE {"^[1-9]{0,1}$"};
        QString settingSS {"border : 2px solid black;"
                               "background : white;"
                               "height : 50px;"
                               "width : 50px;"
                               "color : black;"
                               "font-size : 20px"};
        QRegularExpression possibilitiesRE {"^[1-9]{0,9}$"}; // TODO: allow for an additional character when setting mode is true but validate is false.
        QString possibilitiesSS { "border : 2px solid black;"
                                  "background : white;"
                                  "height : 50px;"
                                  "width : 50px;"
                                  "color : black;"
                                  "font-size : 10px"};
        QValidator* forceTheseValuesWhenSetting = new QRegularExpressionValidator(settingRE, this);
        QValidator* forceTheseValuesWhenPossibilitying = new QRegularExpressionValidator(possibilitiesRE, this);
        bool settingMode = true; // inputMode being true means set number mode, false means possibilities mode.
};


#endif //WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H