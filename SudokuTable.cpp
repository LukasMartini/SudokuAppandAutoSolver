//
// Created by Luke Martin on 2023-03-27.
//

#include "SudokuTable.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert> // TODO: find a better way to handle conditions than this (throw errors probably)

SudokuTable::SudokuTable() {
    this->table = SudokuTable::populateNewTileList();
}

SudokuTable::SudokuTable(std::ifstream &file) {

}

bool SudokuTable::verifyTL(TileList &t) const {
    if (t.size() != 81) {return false;}
    // POSSIBLE TODO: depending on how changes to Tile.value are implemented, a test for whether the value is valid may need to be included.
    for (TileList::iterator it = t.begin(); it != t.end(); it++) {
        if ((it->value == -1 || it->possibilities.empty()) && it->isSet) {return false;}
        if (it->value != -1 && !it->isSet) {return false;}
        // Simply verifies that each tile who has the default value or has no remaining possible values is not also set.
    }
    return true;
}

std::vector<int> SudokuTable::findBoxIndexes(int &index) const {
    return {index};
}
std::vector<int> SudokuTable::findRowIndexes(int &index) const {
    int baseIndex = index - (index % 9);
    int iterIndex = baseIndex;
    std::vector<int> rowIndexes;

    while (iterIndex < index + 9) {
        if (iterIndex != index) {
            rowIndexes.push_back(iterIndex);
        }
        iterIndex++;
    }

    return rowIndexes;
}
std::vector<int> SudokuTable::findColIndexes(int &index) const {
    int baseIndex = index % 9; // Creates the index along the top row in the same column as the argument index
    std::vector<int> colIndexes;

    while (baseIndex < 72) {
        if (baseIndex != index){
            colIndexes.push_back(baseIndex);
        }
        baseIndex += 9;
    }

    return colIndexes;
}

TileList SudokuTable::populateNewTileList() {
    // Preconditions:
    // Implementation:
    TileList newList;
    for (int i = 0; i < 81; i++) {
        Tile newTile = {
                -1,
                {1,2,3,4,5,6,7,8,9},
                {SudokuTable::findBoxIndexes(i), SudokuTable::findRowIndexes(i), SudokuTable::findColIndexes(i)},
                false
        };
        newList.push_back(newTile);
    }
    // Postconditions:
    assert(SudokuTable::verifyTL(newList));

    return newList;
}

TileList SudokuTable::populateNewTileList(std::map<int, int> &presetValues) {

}