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
        SudokuTable currentTable;
        std::map<int, QLineEdit*> tileInputBoxes;
        QRegularExpression settingRE {"^[1-9]{0,1}$"};
        QRegularExpression possibilitiesRE {"^[1-9]{0,9}$"};
        QValidator* forceTheseValuesWhenSetting = new QRegularExpressionValidator(settingRE, this);
        QValidator* forceTheseValuesWhenPossibilitying = new QRegularExpressionValidator(possibilitiesRE, this);
        bool settingMode = true; // inputMode being true means set number mode, false means possibilities mode.
};


#endif //WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H