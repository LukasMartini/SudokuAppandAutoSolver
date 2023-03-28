//
// Created by Luke Martin on 2023-03-27.
//

#include "SudokuTable.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert> // TODO: find a better way to handle conditions than this (throw errors probably)

SudokuTable::SudokuTable() {
    TileList table = SudokuTable::populateNewTileList();
}

SudokuTable::SudokuTable(std::ifstream &file) {

}

bool SudokuTable::verifyTL(TileList &t) const {
    if (t.size() != 81) {return false;}
    for (TileList::iterator it = t.begin(); it != t.end(); it++) {
        if ((it->value == -1 || it->possibilities.size() == 0) && it->isSet) {return false;}
        // Simply verifies that each tile who has the default value or has no remaining possible values is not also set.
    }
    return true;
}

std::vector<int> SudokuTable::findBoxIndexes(int &index) {}
std::vector<int> SudokuTable::findRowIndexes(int &index) {}
std::vector<int> SudokuTable::findColIndexes(int &index) {}

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
    }
    // Postconditions:
    assert(SudokuTable::verifyTL(newList));

    return newList;
}

TileList SudokuTable::populateNewTileList(std::map<int, int> &presetValues) {

}