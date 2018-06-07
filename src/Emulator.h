//
// Created by shinigami on 01/06/18.
//

#ifndef ATTINY13_EMULATOR_EMULATOR_H
#define ATTINY13_EMULATOR_EMULATOR_H

#include "ATTinyMemory/ATtiny13.h"
#include <algorithm>
#include "Instructions.h"

namespace emulator {
    class Emulator{
    public:
        Emulator();
        //todo: modify state
        ~Emulator()=default;
        void execute();
        InstructionSet instructionSet;
        ATtiny13 state;
    };
}

#endif //ATTINY13_EMULATOR_EMULATOR_H
