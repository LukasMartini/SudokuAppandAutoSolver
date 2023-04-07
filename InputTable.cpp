//
// Created by Luke Martin on 2023-04-06.
//

#include "InputTable.h"


// ----- InputTable DEFINITIONS ----- //
InputTable::InputTable() {
    // TODO: update class members to get rid of unnecessary ones. Remember to give them parent=this.
    this->tableLayout = new QGridLayout;
    for (int i = 0; i < 81; i++) {
        auto* newBox = new QLineEdit;
        // TODO: change font sizes and text locations to be approprate for mode
        newBox->setStyleSheet({
          "border : 2px solid black;"
          "background : white;"
          "height : 50px;"
          "width : 50px;"
          "color : black"
        });
        newBox->setValidator(this->forceTheseValuesWhenSetting); // This is the default validator.
        connect(newBox, &QLineEdit::textChanged, this, &InputTable::returnUpdatedTileValue);
        this->tileInputBoxes[i] = newBox;
        this->tableLayout->addWidget(newBox, i - (i % 9), i % 9, 1, 1);
    }
    this->tableLayout->setSpacing(0);
    this->tableLayout->setContentsMargins(0,0,0,0);
}

int InputTable::returnUpdatedTileValue(QString newVal) {
    return newVal.toInt();
}

void InputTable::switchMode() {
    this->settingMode = !this->settingMode;
    std::cout << this->settingMode;
    for (auto & boxes : this->tileInputBoxes) {
        if (this->settingMode) {
            boxes.second->setValidator(this->forceTheseValuesWhenSetting);
        } else {
            boxes.second->setValidator(this->forceTheseValuesWhenPossibilitying);
        }
    }
}