//
// Created by Luke Martin on 2023-03-27.
//
#ifndef WAVECOLLAPSESUDOKUSOLVER_SUDOKUTABLE_H
#define WAVECOLLAPSESUDOKUSOLVER_SUDOKUTABLE_H

#include "WFC.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "gtest/gtest.h"

struct Tile {
    int value = -1; // -1 is the default, unset value. I would've preferred to use a more descriptive string, but typecasting is for losers.
    std::vector<std::vector<int>> adjacencies;
    bool isSet; // A flag used when the number CANNOT be changed (like the numbers given to you at the start of a puzzle)
    bool displayPossibilities;
};
typedef std::vector<Tile> TileList;

class SudokuTable {
    public:
        SudokuTable();
        SudokuTable(std::map<int, int> presetValues, bool setValues);
        SudokuTable(std::ifstream &file, bool setValues);
        void updateTable(const std::map<int, int> &changedValues);
        std::map<int, int> getTileValues();
        Tile getTile(int index);

    private:
        bool verifyTL(TileList &t) const;
        TileList populateNewTileList();
        TileList populateNewTileList(std::map<int, int> &presetValues, bool setValues); // Overloaded version that handles presets
        TileList populateNewTileList(std::ifstream &file, bool setValues);
        std::vector<int> findBoxIndexes(int &index) const;
        std::vector<int> findRowIndexes(int &index) const;
        std::vector<int> findColIndexes(int &index) const;

        TileList table;
        WFC waveFunction;

    // ---------- FRIEND TEST SECTION ---------- //
        // ----- defaultCtorSuite ----- //
        FRIEND_TEST(defaultCtorSuite, givenNoInputEnsureValidTable);

        // ----- verifyTLSuite ----- //
        FRIEND_TEST(verifyTLSuite, flagSetWhileValueStillDefaultExpectDeath);
        FRIEND_TEST(verifyTLSuite, valueOutsideOfExpectedRangeExpectDeath);

        // ----- populateNewTileListMapOverloadedSuite ----- //
        FRIEND_TEST(populateNewTileListMapOverloadedSuite, supplyValidPresetsExpectCorrectValues);
        FRIEND_TEST(populateNewTileListMapOverloadedSuite, supplyInvalidPositiveKeysExpectFailure);
        FRIEND_TEST(populateNewTileListMapOverloadedSuite, supplyInvalidPositiveValuesExpectFailure);
        FRIEND_TEST(populateNewTileListMapOverloadedSuite, supplyInvalidNegativeKeysExpectFailure);
        FRIEND_TEST(populateNewTileListMapOverloadedSuite, supplyInvalidNegativeValuesExpectFailure);

        // ----- populateNewTileListFileOverloadedSuite ----- //
        FRIEND_TEST(populateNewTileListFileOverloadedSuite, givenValidFileWithValidMapExpectValidTable);
        FRIEND_TEST(populateNewTileListFileOverloadedSuite, givenValidFileWithInvalidMapExpectDeath); // More of an integration test ig?
        FRIEND_TEST(populateNewTileListFileOverloadedSuite, givenInvalidFileExpectDeath);

        // ----- findBoxIndexesSuite ----- //
        FRIEND_TEST(findBoxIndexesSuite, givenBaseTableEnsureCorrectBoxIndexes);

        // ----- findRowIndexesSuite ----- //
        FRIEND_TEST(findRowIndexesSuite, givenBaseTableEnsureCorrectRowIndexes);

        // ----- findColIndexesSuite ----- //
        FRIEND_TEST(findColIndexesSuite, givenBaseTableEnsureCorrectColIndexes);

        // ----- getTileValuesSuite ----- //
        FRIEND_TEST(getTileValuesSuite, givenValidEmptyTableExpectCorrectValuesReturned);
        FRIEND_TEST(getTileValuesSuite, givenValidPopulatedTableExpectCorrectValuesReturned);
//
//        // ----- updateTableSuite ----- //
//        FRIEND_TEST(updateTableSuite, givenValidValuesExpectValidUpdate);
//        FRIEND_TEST(updateTableSuite, givenInvalidValuesExpectDeath);
};

#endif