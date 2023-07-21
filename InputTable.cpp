//
// Created by Luke Martin on 2023-04-06.
//

#include "InputTable.h"

// TODO: standardize "boxes" to "tiles"

// ----- Ctor, Dtor, and Other Important Functions ----- //
InputTable::InputTable() {
    this->tableLayout = new QGridLayout;
    for (int i = 0; i < 81; i++) {
        auto* newBox = new QLineEdit;
        newBox->setStyleSheet(this->settingSS); // This is the default stylesheet
        newBox->setValidator(this->forceTheseValuesWhenSetting); // This is the default validator.
        connect(newBox, &QLineEdit::textChanged, this, &InputTable::returnUpdatedTileValue);
        this->tileInputBoxes[i] = newBox;
        this->tableLayout->addWidget(newBox, i - (i % 9), i % 9, 1, 1);
    }
    this->tableLayout->setSpacing(0);
    this->tableLayout->setContentsMargins(0,0,0,0);
}

// ----- Getters ----- //
std::map<int, int> InputTable::getInputTableValues() const {
    std::map<int, int> tableValues;
    for (auto & tiles : this->tileInputBoxes) {
        tiles.second->text().isEmpty() ? tableValues[tiles.first] = -1 : tableValues[tiles.first] = tiles.second->text().toInt(); // NOTE: this is guaranteed to be a safe type change because the regexes never allow non-numeric characters.
    }
    return tableValues;
}

bool InputTable::getSettingMode() const {
    return this->settingMode;
}

// ----- Setters ----- //
void InputTable::setCurrentTable(SudokuTable* newTable) {
    this->currentTable = newTable; // Sets the currentTable field to the new data.
    for (auto &it : this->currentTable->getTileValues()) { // Iterates over all the tile values to display them and to format as required.
        this->tileInputBoxes[it.first]->setEnabled(true); // Resets the setEnabled flag to allow for changes when reading from a different file.
        if (it.second != -1) { // If there is a value in that box...
            if (this->currentTable->getTile(it.first).displayPossibilities) { // And if the "value" is actually a list of possibilities...
                this->settingMode = false; // This tricks the returnUpdatedTileValue slot into thinking that it's in possibilities mode for just this tile to get the validator and stylesheet right.
                this->tileInputBoxes[it.first]->setValidator(this->forceTheseValuesWhenPossibilitying); // Set the right validator and stylesheet manually.
                this->tileInputBoxes[it.first]->setStyleSheet(this->possibilitiesSS);
            }
            this->tileInputBoxes[it.first]->setText(QString::number(it.second)); // Sets the input box's text to the value of the tile in the save data.
            this->settingMode = true; // Resets the setting mode to stay in the correct display mode when writing into the table from a file.
        } else {
            this->tileInputBoxes[it.first]->setText(QString ("")); // If there isn't a value to be written to the screen, leave it blank.
        }

        if (this->currentTable->getTile(it.first).isSet) { // Handles values that can't be changed.
            this->tileInputBoxes[it.first]->setStyleSheet(this->setValueSS);
            this->tileInputBoxes[it.first]->setEnabled(false); // TODO: consider a special stylesheet for these boxes to avoid confusion.
        }
    }
}

// ----- Pass-off from InputWindow's Slots ----- //
void InputTable::saveTable(std::ofstream &file){ //
    if (this->currentTable) { // Updates or creates a new table...
        this->currentTable->updateTable(this->getInputTableValues());
    } else {
        this->currentTable = new SudokuTable(this->getInputTableValues(), false);
    }
    for (int tile = 0; tile < 81; tile++) { // ...from which the data is read into the file.
        Tile currentTile = this->currentTable->getTile(tile);
        if (currentTile.value > 9) {
            currentTile.displayPossibilities = true;
        }
        file << std::to_string(tile) << " " << std::to_string(currentTile.value) << " [" << this->makePrintableVectorOfVectors(currentTile.adjacencies)
        << "] " << currentTile.isSet << " " << currentTile.displayPossibilities << std::endl;
    }
}

// ----- Validation Functions ----- //
bool InputTable::validateLength(const QString& values) const {
    return (this->settingMode ? values.length() <= 1 : values.length() <= 9);
}

int InputTable::validateNoDuplicates(const std::string &values) {
    for (int i = 0; i < values.length(); i++) {
        if (i != values.length() - 1 && values.at(i) == values.at(i+1)) {
            return i;
        }
    }
    return -1;
}

// ----- Slot Definitions ----- //
int InputTable::returnUpdatedTileValue(const QString& newVal) {
    auto* box = qobject_cast<QLineEdit*>(sender());
    if (this->settingMode && !this->validateLength(newVal)) {
        QString newSetValue = newVal.at(newVal.length()-1);
        box->setValidator(this->forceTheseValuesWhenSetting);
        box->setStyleSheet(this->settingSS);
        box->setText(newSetValue);
    } else if (this->settingMode) { // NOTE: this should run if this->validateLength returns true. It was not included for brevity.
        box->isEnabled() ? box->setStyleSheet(this->settingSS) : box->setStyleSheet(this->setValueSS);
    } else {
        box->setStyleSheet(this->possibilitiesSS);
        std::string sortableNewVal = newVal.toStdString(); // Had bad access issues, just converted to string instead.
        sort(sortableNewVal.begin(), sortableNewVal.end()); // Sorts the string to make duplicate checking possible and cleans the UI.
        int duplicateIndex = this->validateNoDuplicates(sortableNewVal);
        if (duplicateIndex != -1) {
            box->setText(QString::fromStdString(sortableNewVal.substr(0, duplicateIndex) + sortableNewVal.substr(duplicateIndex+1, sortableNewVal.length()-1)));
        } else {
            box->setText(QString::fromStdString(sortableNewVal));
        }
    }
    return newVal.toInt();
}

void InputTable::switchMode() {
    this->settingMode = !this->settingMode;
    for (auto & boxes : this->tileInputBoxes) {
        if (this->settingMode && this->validateLength(boxes.second->text())) {
            boxes.second->setValidator(this->forceTheseValuesWhenSetting);
        } else {
            boxes.second->setValidator(this->forceTheseValuesWhenPossibilitying);
        }
    }
}

// ----- Additional Helper Functions ----- //
std::string InputTable::makePrintableVector(std::vector<int> target) {
    std::string result = "";
    for (int itemIndex = 0; itemIndex < target.size(); itemIndex++) {
        itemIndex + 1 < target.size() ? result += (std::to_string(target.at(itemIndex)) + ", ") : result += std::to_string(target.at(itemIndex));
    }
    return result;
}

std::string InputTable::makePrintableVectorOfVectors(std::vector<std::vector<int>> target) {
    std::string result = "";
    for (int vectorIndex = 0; vectorIndex < target.size(); vectorIndex++) {
        vectorIndex + 1 < target.size() ? result += ("[" + this->makePrintableVector(target.at(vectorIndex)) + "], ") : result += ("[" + this->makePrintableVector(target.at(vectorIndex)) + "]");
    }
    return result;
}