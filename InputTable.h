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

        void saveTable(std::ofstream &file);

        std::map<int, int> getInputTableValues() const;

    public slots:
        int returnUpdatedTileValue(const QString&);
        void switchMode();

    private:
        SudokuTable currentTable;
        std::map<int, QLineEdit*> tileInputBoxes;

        bool validateLength(const QString& values) const;
        static bool validateNoDuplicates(const std::string &values);

        const QRegularExpression settingRE {"^[1-9]{0,1}$"};
        const QString settingSS {"border : 2px solid black;"
                               "background : white;"
                               "height : 50px;"
                               "width : 50px;"
                               "color : black;"
                               "font-size : 20px"};
        const QRegularExpression possibilitiesRE {"^[1-9]{0,9}$"}; // TODO: allow for an additional character when setting mode is true but validate is false.
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