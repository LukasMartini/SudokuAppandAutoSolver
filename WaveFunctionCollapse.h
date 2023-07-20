//
// Created by Luke Martin on 2023-07-19.
//

#ifndef WAVECOLLAPSESUDOKUSOLVER_WAVEFUNCTIONCOLLAPSE_H
#define WAVECOLLAPSESUDOKUSOLVER_WAVEFUNCTIONCOLLAPSE_H

#include "SudokuTable.h"

class WaveFunctionCollapse {
    public:
        WaveFunctionCollapse();
        SudokuTable* runWFC(SudokuTable* table);

};


#endif //WAVECOLLAPSESUDOKUSOLVER_WAVEFUNCTIONCOLLAPSE_H
