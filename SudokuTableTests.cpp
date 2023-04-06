//
// Created by Luke Martin on 2023-03-28.
//
#include "SudokuTable.h"
#include "gtest/gtest.h"
#include <iostream>
#include <map>


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

TEST (verifyTLSuite, missingFlagSetAfterChangeToTableExpectDeath) {
    SudokuTable st;
    st.table.at(0).value = 2;
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
    SudokuTable st {presets};

    EXPECT_TRUE(st.verifyTL(st.table));
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidPositiveKeysExpectFailure) {
    std::map<int, int> presets;
    presets[380] = 4;
    EXPECT_DEATH(SudokuTable st {presets}, "");
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidPositiveValuesExpectFailure) {
    std::map<int, int> presets;
    presets[38] = 420;
    EXPECT_DEATH(SudokuTable st {presets}, "");
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidNegativeKeysExpectFailure) {
    std::map<int, int> presets;
    presets[-38] = 4;
    EXPECT_DEATH(SudokuTable st {presets}, "");
}

TEST (populateNewTileListMapOverloadedSuite, supplyInvalidNegativeValuesExpectFailure) {
    std::map<int, int> presets;
    presets[38] = -4;
    EXPECT_DEATH(SudokuTable st {presets}, "");
}

// ----- populateNewTileListFileOverloadedSuite ----- //
TEST (populateNewTileListFileOverloadedSuite, givenValidFileWithValidMapExpectValidTable) {
    std::ifstream file {"testCaseFiles/SudokuTableValidFileValidMapTest.txt"};
    SudokuTable st {file};
    EXPECT_TRUE(st.verifyTL(st.table));
}

TEST (populateNewTileListFileOverloadedSuite, givenValidFileWithInvalidMapExpectDeath) {
    std::ifstream file {"testCaseFiles/SudokuTableValidFileInvalidMapTest.txt"};
    EXPECT_DEATH(SudokuTable st {file}, "");
}

TEST (populateNewTileListFileOverloadedSuite, givenInvalidFileExpectDeath) {
    std::ifstream file {"BonjourJemappelleOrange.csv"};
    EXPECT_DEATH(SudokuTable st {file}, "");
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

// ---- findColIndexesSuite ----- //
TEST (findColIndexesSuite, givenBaseTableEnsureCorrectColIndexes) {
    SudokuTable st;
    for (int tile = 0; tile < 81; tile++) {
        for (auto &colIt : st.table.at(tile).adjacencies.at(2)) {
            EXPECT_TRUE(colIt != tile); // Ensures that the given index is not present in it's adjacency column list
            EXPECT_TRUE(colIt % 9 == tile % 9); // Ensures that all values in a given column have the same base row square
        }
    }
}