//
// Created by shinigami on 01/06/18.
//

#ifndef ATTINY13_EMULATOR_INSTRUCTIONSET_H
#define ATTINY13_EMULATOR_INSTRUCTIONSET_H

#include "../instruction/Instruction.h"
#include <set>
#include <algorithm>

namespace emulator {

    ///porównanie wskażników na instrukcje
    class InstructionCompare {
    public:
        bool operator () (const Instruction *a, const Instruction *b) {
            return (*a) < (*b);
        }
    };

    //zawiera wskażniki na instrukjce - umożliwia ich efektywne wyszukiwanie (w przyszłośći)
    class InstructionSet : public std::set<Instruction *,InstructionCompare> {
    public:
        iterator find(uint16_t programInstruction){ //TODO: improve search algorithm
            return std::find_if(begin(),end(),[&programInstruction](const Instruction* i){
                return *i==programInstruction;
            });
        }
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTIONSET_H
