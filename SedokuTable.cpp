//
// Created by Luke Martin on 2023-03-27.
//

#include "SedokuTable.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <cassert> // TODO: find a better way to handle conditions than this (throw errors probably)

SedokuTable::SedokuTable() {
    TileList table = SedokuTable::populateNewTileList();
}

SedokuTable::SedokuTable(std::ifstream &file) {

}

bool SedokuTable::verifyTL(TileList &t) const {
    if (t.size() != 81) {return false;}
    for (TileList::iterator it = t.begin(); it != t.end(); it++) {
        if ((it->value == -1 || it->possibilities.size() == 0) && it->isSet) {return false;}
        // Simply verifies that each tile who has the default value or has no remaining possible values is not also set.
    }
    return true;
}

std::vector<int> SedokuTable::findBoxIndexes(int &index) {}
std::vector<int> SedokuTable::findRowIndexes(int &index) {}
std::vector<int> SedokuTable::findColIndexes(int &index) {}

TileList SedokuTable::populateNewTileList() {
    // Preconditions:
    // Implementation:
    TileList newList;
    for (int i = 0; i < 81; i++) {
        Tile newTile = {
                -1,
                {1,2,3,4,5,6,7,8,9},
                {SedokuTable::findBoxIndexes(i), SedokuTable::findRowIndexes(i), SedokuTable::findColIndexes(i)},
                false
        };
    }
    // Postconditions:
    assert(SedokuTable::verifyTL(newList));

    return newList;
}

TileList SedokuTable::populateNewTileList(std::map<int, int> &presetValues) {

}