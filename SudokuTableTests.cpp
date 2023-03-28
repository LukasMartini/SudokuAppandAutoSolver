//
// Created by Luke Martin on 2023-03-28.
//
#include "SudokuTable.h"
#include "gtest/gtest.h"

TEST (defaultCtorSuite, givenNoInputEnsureEmptyTable) {
    SudokuTable emptyTable {}; // Create new table with input-less ctor
    ASSERT_TRUE(emptyTable.verifyTL(emptyTable.table));
}


