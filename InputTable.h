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
        bool inputMode = true; // inputMode being true means set number mode, false means possibilities mode.
};


#endif //WAVECOLLAPSESUDOKUSOLVER_INPUTTABLE_H