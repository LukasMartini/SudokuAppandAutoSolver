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
    std::vector<int> possibilities;
    const std::vector<std::vector<int>> adjacencies;
    bool isSet;
    bool displayPossibilities;
};
typedef std::vector<Tile> TileList;

class SudokuTable {
    public:
        SudokuTable();
        SudokuTable(std::map<int, int> &presetValues);
        SudokuTable(std::ifstream &file);
        void updateTable(const std::map<int, int> &changedValues);

    private:
        bool verifyTL(TileList &t) const;
        TileList populateNewTileList();
        TileList populateNewTileList(std::map<int, int> &presetValues); // Overloaded version that handles presets
        TileList populateNewTileList(std::ifstream &file);
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
        FRIEND_TEST(verifyTLSuite, missingFlagSetAfterChangeToTableExpectDeath);
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
};

#endif