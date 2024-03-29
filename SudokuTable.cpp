//
// Created by Luke Martin on 2023-03-27.
//

#include "SudokuTable.h"
#include <iostream>
#include <vector>
#include <cassert> // TODO: find a better way to handle conditions than this (throw errors probably)
#include <string>

// ----- Ctors ----- //
SudokuTable::SudokuTable() {
    this->table = this->populateNewTileList();
}

SudokuTable::SudokuTable(std::map<int, int> presetValues, bool setValues) {
    this->table = this->populateNewTileList(presetValues, setValues);
}

SudokuTable::SudokuTable(std::ifstream &file, bool setValues) {
    this->table = this->populateNewTileList(file, setValues);
}

// ----- Verifiers ----- //
bool SudokuTable::verifyTL(TileList &t) const {
    // Preconditions:
    // Implementation:
    if (t.size() != 81) {return false;}
    for (TileList::iterator it = t.begin(); it != t.end(); it++) {
        if (it->value > 9 && it->isSet) { // NOTE: no value == -1 check is required because the regexes enforce any non-(-1) values to be >0
            return false;
        }
        // TODO: add a regex check on possibilities.
        if (it->value != -1 && it-> value <= 0){
            return false;
        }
        if (it->displayPossibilities && it->isSet) {
            return false;
        }
    }
    // Postconditions:
    // Return Value:
    return true;
}

// ----- Getters ----- //
std::map<int, int> SudokuTable::getTileValues() { // TODO: write unit tests
    // Preconditions:
    assert(this->verifyTL(this->table));
    // Implementation:
    std::map<int, int> tileNumbersMappedToTileValues;
    for (int tile = 0; tile < 81; tile++) {
        tileNumbersMappedToTileValues[tile] = this->table.at(tile).value;
    }
    // Postconditions:
    // Return Value:
    return tileNumbersMappedToTileValues;
}

Tile SudokuTable::getTile(int index) { // TODO: write unit tests
    // Preconditions:
    assert(this->verifyTL(this->table));
    // Implementation:
    // Postconditions:
    // Return Value:
    return this->table.at(index);
}

// ----- Hand-offs From InputWindow.cpp ----- //
void SudokuTable::updateTable(const std::map<int, int> &changedValues) {
    // Preconditions:
    for (auto &it : changedValues) {
        assert(it.first >= 0 && it.first <= 80);
        assert(it.second == -1 || it.second > 0);
    }
    // Implementations:
    for (auto &it : changedValues) {
        this->table.at(it.first).value = it.second;
    }
    // Postconditions:
    assert(this->verifyTL(this->table));
    // Return Value:
}

// ----- Populators ----- //
TileList SudokuTable::populateNewTileList() {
    // Preconditions:
    // Implementation:
    TileList newList;
    for (int i = 0; i < 81; i++) {
        Tile newTile = {
                -1,
                {this->findBoxIndexes(i), this->findRowIndexes(i), this->findColIndexes(i)},
                false,
                true,
        };
        newList.push_back(newTile);
    }
    // Postconditions:
    assert(this->verifyTL(newList));
    // Return Value:
    return newList;
}

TileList SudokuTable::populateNewTileList(std::map<int, int> &presetValues, bool setValues) {
    /*
      // ----- MAP FORMATTING REQUIREMENTS ----- //
        -> The key must be the tile (index) for which the value is to be assigned (from 0 to 80 inclusive)
        -> The value must be a number from 1 to 9 inclusive, exclusively
      // ----- /MAP FORMATTING REQUIREMENTS ----- //
    */
    // Preconditions:
    for (auto &mapIt : presetValues) {
        assert(mapIt.first >= 0 && mapIt.first <= 80);
        assert(mapIt.second == -1 || mapIt.second > 0);
    }
    // Implementation:
    TileList newList = this->populateNewTileList(); // Creates a blank table
    for (auto &preset : presetValues) {
        newList.at(preset.first).value = preset.second; // Sets preset value
        if (preset.second != -1) {
            newList.at(preset.first).isSet = setValues; // Sets the flag to keep track of unchangeable values
        }
        newList.at(preset.first).displayPossibilities = false; // This defaults all tiles to be false. They will be flipped to true in the file override of it is relevant.
    }
    // Postconditions:
    assert(this->verifyTL(newList));
    // Return Value:
    return newList; // Dumbass. Of course you're gonna get SIGTRAP'd if you don't return a value. Dipshit.

}

TileList SudokuTable::populateNewTileList(std::ifstream &file, bool setValues) {
    // Preconditions
    assert(!file.fail());
    // Implementation:
    std::map<int, int> filePresets;
    std::string preset;
    std::vector<int> doIDisplayPossibilities (81);
    std::vector<int> amIASetValue (81);
    while (getline(file, preset)) {
        int key = std::stoi(preset.substr(0, preset.find(' ')));
        int value = std::stoi(preset.substr(preset.find(' ') + 1, preset.find('[') - 1));
        filePresets[key] = value;
        doIDisplayPossibilities.at(key) = int(preset.at(preset.length() - 1)) - 48; // Subtracting by 48 returns the character to it's correct numerical value because of ASCII jank.
        amIASetValue.at(key) = int(preset.at(preset.length() - 3)) - 48;
    }
    TileList newList = this->populateNewTileList(filePresets, setValues);
    for (int tile = 0; tile < 81; tile++) {
        newList.at(tile).displayPossibilities = doIDisplayPossibilities.at(tile);
        newList.at(tile).isSet = amIASetValue.at(tile);
    }
    // Postconditions:
    assert(this->verifyTL(newList));
    // Return Value:
    return newList;

}

// ----- Index Builders ----- //
std::vector<int> SudokuTable::findBoxIndexes(int &index) const {
    // Preconditions:
    // Implementation:
    std::vector<int> boxIndexes;
    int row = (index - (index % 9)) / 9; // This gives you a number between 0 and 8.
    int col = index % 9; // This also gives you a number between 0 and 8.
    // EX: tile 12 is in row 1 and column 3 when zero indexed. This pattern holds such that an index is always (row*9 + col)
    int targetRow = row < 3 ? 0 : (row < 6 ? 3 : 6); // Finds the closest top row of a given section
    int targetCol = col < 3 ? 0 : (col < 6 ? 3 : 6); // Finds the closest left-most column of a given section
    int targetTile = (targetRow * 9) + targetCol;
    // EX: tile 0 would be the target row and col of all tiles in the top left section (indexes 0,1,2,9,10,11,18,19,20)
    for (int allTiles = 0; allTiles < 3; allTiles++) { // There are three rows, this shifts through each one
        for (int boxRow = targetTile; boxRow < targetTile+3; boxRow++) { // Goes through the three tiles per row in a box.
            if (boxRow != index) {
                boxIndexes.push_back(boxRow);
            }
        }
        targetTile += 9; // Shifts to the row below
    }
    // Postconditions:
    // Return Value:
    return boxIndexes;
}
std::vector<int> SudokuTable::findRowIndexes(int &index) const {
    // Preconditions:
    // Implementation:
    int baseIndex = index - (index % 9);
    int iterIndex = baseIndex;
    std::vector<int> rowIndexes;

    while (iterIndex < baseIndex + 9) {
        if (iterIndex != index) {
            rowIndexes.push_back(iterIndex);
        }
        iterIndex++;
    }
    // Postconditions:
    // Return Value:
    return rowIndexes;
}
std::vector<int> SudokuTable::findColIndexes(int &index) const {
    // Preconditions:
    // Implementation:
    int baseIndex = index % 9; // Creates the index along the top row in the same column as the argument index
    std::vector<int> colIndexes;

    while (baseIndex < 81) {
        if (baseIndex != index){
            colIndexes.push_back(baseIndex);
        }
        baseIndex += 9;
    }
    // Postconditions:
    // Return Value:
    return colIndexes;
}