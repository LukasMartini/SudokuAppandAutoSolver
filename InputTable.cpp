//
// Created by Luke Martin on 2023-04-06.
//

#include "InputTable.h"


// ----- InputTable DEFINITIONS ----- //
InputTable::InputTable() {
    // TODO: add input mask after mode switching has been dealt with.
    // TODO: update class members to get rid of unnecessary ones. Remember to give them parent=this.
    this->tableLayout = new QGridLayout;
    for (int i = 0; i < 81; i++) {
        QLineEdit* newBox = new QLineEdit;
        newBox->setStyleSheet({
                                      "border : 2px solid black;"
                                      "background : white;"
                                      "height : 50px;"
                                      "width : 50px;"
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

void InputTable::switchMode() {
    this->inputMode = !this->inputMode;
}