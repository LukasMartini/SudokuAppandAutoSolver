//
// Created by Luke Martin on 2023-03-28.
//
#include "SudokuTable.h"
#include "gtest/gtest.h"
#include <iostream>
#include <map>

// A NOTE ABOUT FILE PATHS (for me because I am dumb): The directory that is being checked is /cmake-build-debug/, so
// ../ needs to be added in front of TestCaseFiles file paths in order to look for the right directory.

// ----- defaultCtorSuite ----- //
TEST (defaultCtorSuite, givenNoInputEnsureValidTable) {
    SudokuTable emptyTable; // Create new table with input-less ctor
    ASSERT_TRUE(emptyTable.verifyTL(emptyTable.table));
}

// ----- verifyTLSuite ----- //
TEST (verifyTLSuite, flagSetWhileValueStillDefaultExpectDeath) {
    SudokuTable st;
    st.table.at(80).isSet = true;
    EXPECT_FALSE(st.verifyTL(st.table));
}

TEST (verifyTLSuite, valueOutsideOfExpectedRangeExpectDeath) {
    SudokuTable st;
    st.table.at(69).value = -400;
    st.table.at(69).isSet = true;
    EXPECT_FALSE(st.verifyTL(st.table));
    st.table.at(69).value = 9001;
    EXPECT_FALSE(st.verifyTL(st.table));
}

// ----- populateNewTileListMapOverloadedSuite ----- //
TEST (populateNewTileListMapOverloadedSuite, supplyValidPresetsExpectCorrectValues) {
    std::map<int, int> presets;
    presets[10] = 8;
    presets[23] = 2;
    presets[15] = 1;
    presets[38] = 4;
    presets[30] = 7;
    presets[51] = 5;
    presets[73] = 3;
    presets[58] = 6;
    presets[62] = 9;
    SudokuTable st {presets, false};

    EXPECT_TRUE(st.verifyTL(st.table));
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidPositiveKeysExpectFailure) {
    std::map<int, int> presets;
    presets[380] = 4;
    EXPECT_DEATH(SudokuTable st (presets, false), "");
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidPositiveValuesExpectFailure) {
    std::map<int, int> presets;
    presets[38] = 420;
    EXPECT_DEATH(SudokuTable st (presets, false), "");
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidNegativeKeysExpectFailure) {
    std::map<int, int> presets;
    presets[-38] = 4;
    EXPECT_DEATH(SudokuTable st (presets, false), "");
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidNegativeValuesExpectFailure) {
    std::map<int, int> presets;
    presets[38] = -4;
    EXPECT_DEATH(SudokuTable st (presets, false), "");
}

// ----- populateNewTileListFileOverloadedSuite ----- //
TEST (populateNewTileListFileOverloadedSuite, givenValidFileWithValidMapExpectValidTable) {
    std::ifstream file {"../TestCaseFiles/SudokuTableValidFileValidMapTest.txt"};
    SudokuTable st (file, false);
    EXPECT_TRUE(st.verifyTL(st.table));
}

TEST (populateNewTileListFileOverloadedSuite, givenValidFileWithInvalidMapExpectDeath) {
    std::ifstream file {"../TestCaseFiles/SudokuTableValidFileInvalidMapTest.txt"};
    EXPECT_DEATH(SudokuTable st (file, false), "");
}

TEST (populateNewTileListFileOverloadedSuite, givenInvalidFileExpectDeath) {
    std::ifstream file {"BonjourJeM'appelleOrange.csv"};
    EXPECT_DEATH(SudokuTable st (file, false), "");
}

// ----- findBoxIndexesSuite ----- //
TEST (findBoxIndexesSuite, givenBaseTableEnsureCorrectBoxIndexes) {
    SudokuTable st;
    for (int tile = 0; tile < 81; tile++) {
        int row = (tile - (tile % 9)) / 9;
        int targetTileRow = row < 3 ? 0 : (row < 6 ? 3 : 6);
        int col = tile % 9;
        int targetTileCol = col < 3 ? 0 : (col < 6 ? 3 : 6);
        for (auto &boxIt : st.table.at(tile).adjacencies.at(0)) {
            EXPECT_TRUE(boxIt != tile);
            int boxItRow = (boxIt - (boxIt % 9)) / 9;
            int targetBoxItRow = boxItRow < 3 ? 0 : (boxItRow < 6 ? 3 : 6);
            EXPECT_TRUE(targetTileRow == targetBoxItRow);
            int boxItCol = boxIt % 9;
            int targetBoxItCol = boxItCol < 3 ? 0 : (boxItCol < 6 ? 3 : 6);
            EXPECT_TRUE(targetTileCol == targetBoxItCol);
        }
    }
}

// ----- findRowIndexesSuite ----- //
TEST (findRowIndexesSuite, givenBaseTableEnsureCorrectRowIndexes) {
    SudokuTable st;
    for (int tile = 0; tile < 81; tile++) {
        for (auto &rowIt : st.table.at(tile).adjacencies.at(1)) {
            EXPECT_TRUE(rowIt != tile);
            EXPECT_TRUE((rowIt - (rowIt - tile)) % tile == 0);
        }
    }
}

// ----- findColIndexesSuite ----- //
TEST (findColIndexesSuite, givenBaseTableEnsureCorrectColIndexes) {
    SudokuTable st;
    for (int tile = 0; tile < 81; tile++) {
        for (auto &colIt : st.table.at(tile).adjacencies.at(2)) {
            EXPECT_TRUE(colIt != tile); // Ensures that the given index is not present in its adjacency column list
            EXPECT_TRUE(colIt % 9 == tile % 9); // Ensures that all values in a given column have the same base row square
        }
    }
}

// ----- getTileValuesSuite ----- //
TEST (getTileValuesSuite, givenValidEmptyTableExpectCorrectValuesReturned) {
    std::ifstream file {"../TestCaseFiles/SudokuTableValidSaveFileEmptyTable.txt"};
    SudokuTable st (file, false);
    std::map<int, int> filesTiles = st.getTileValues();
    for (auto &tile : filesTiles) {
        EXPECT_EQ(tile.second, -1); // Other tests should ensure that the table is valid. Thus, I am only checking the tile values.
    }
}

TEST (getTileValuesSuite, givenValidPopulatedTableExpectCorrectValuesReturned) {
    std::ifstream file {"../TestCaseFiles/SudokuTableValidSaveFilePopulatedTable.txt"};
    SudokuTable st (file, false);
    std::map<int, int> filesTiles = st.getTileValues();
    EXPECT_EQ(filesTiles[10], 9);
    EXPECT_EQ(filesTiles[47], 1);
    EXPECT_EQ(filesTiles[80], -1); // Redundancy?
}

// NOTE: Due to how the class is set up, building an invalid table should fail before getTileValues() can be called.
// Additionally, using updateTable() should also fail before getTileValues() can be called with an invalid table,
// so making a unit test for it is irrelevant. So is this note, but this is more to remind myself lol.

// ----- updateTableSuite ----- //

/*
TEST (updateTableSuite, givenValidValuesExpectValidUpdate) {
    std::map<int, int> validUpdates;
    validUpdates[6] = 9;
    validUpdates[41] = 1;
    SudokuTable st;
    st.updateTable(validUpdates); // The assertion in the method is the fail condition
}

TEST (updateTableSuite, givenInvalidValuesExpectDeath) {
    std::map<int, int> invalidUpdates;
    invalidUpdates[9] = -6;
    SudokuTable st;
    EXPECT_DEATH(st.updateTable(invalidUpdates), "");
}
*/