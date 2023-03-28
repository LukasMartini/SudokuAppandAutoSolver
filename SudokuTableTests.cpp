//
// Created by Luke Martin on 2023-03-28.
//
#include "SudokuTable.h"
#include "gtest/gtest.h"
#include <iostream>


// ----- defaultCtorSuite ----- //
TEST (defaultCtorSuite, givenNoInputEnsureValidTable) {
    SudokuTable emptyTable; // Create new table with input-less ctor
    ASSERT_TRUE(emptyTable.verifyTL(emptyTable.table));
}

// ----- verifyTLSuite ----- //
TEST (verifyTLSuite, afterInvalidValueChangeToTableEnsureDeath) {
    SudokuTable st;
    st.table.at(0).value = 2;
    ASSERT_FALSE(st.verifyTL(st.table));
}

// ----- findRowIndexesSuite ----- //
TEST (findRowIndexesSuite, givenBaseTableEnsureCorrectRowIndexes) {
    SudokuTable st;
    for (int tile = 0; tile < 81; tile++) {
        for (auto &rowIt : st.table.at(tile).adjacencies.at(1)) {
            ASSERT_TRUE(rowIt != tile);
            ASSERT_TRUE((rowIt - (rowIt - tile)) % tile == 0);
        }
    }
}

// ---- findColIndexesSuite ----- //
TEST (findColIndexesSuite, givenBaseTableEnsureCorrectColIndexes) {
    SudokuTable st;
    for (int tile = 0; tile < 81; tile++) {
        for (auto &colIt : st.table.at(tile).adjacencies.at(2)) {
            ASSERT_TRUE(colIt != tile); // Ensures that the given index is not present in it's adjacency column list
            ASSERT_TRUE(colIt % 9 == tile % 9); // Ensures that all values in a given column have the same base row square
        }
    }
}