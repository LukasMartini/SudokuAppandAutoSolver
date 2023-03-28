//
// Created by Luke Martin on 2023-03-28.
//
#include "SedokuTable.h"
#include "gtest/gtest.h"

TEST (defaultCtorSuite, givenNoInputEnsureEmptyTable) {
    SedokuTable emptyTable {}; // Create new table with input-less ctor
    ASSERT_TRUE(emptyTable.verifyTL(emptyTable.table));
}


