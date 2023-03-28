//
// Created by Luke Martin on 2023-03-27.
//
#include<iostream>
#include<fstream>
#include<vector>
#include<map>

struct Tile {
    int value = -1; // -1 is the default, unset value. I would've preferred to use a more descriptive string, but typecasting is for losers.
    std::vector<int> possibilities;
    const std::vector<std::vector<int>> adjacencies;
    bool isSet;
};
typedef std::vector<Tile> TileList;

class SedokuTable {
    public:
        SedokuTable();
        SedokuTable(std::ifstream &file);
        ~SedokuTable(); // Note that a non-default destructor may not be necessary.

    private:
        bool verifyTL(TileList &t) const;
        TileList populateNewTileList();
        TileList populateNewTileList(std::map<int, int> &presetValues); // Overridden version that handles presets
        std::vector<int> findBoxIndexes(int &index);
        std::vector<int> findRowIndexes(int &index);
        std::vector<int> findColIndexes(int &index);

        TileList table;
};