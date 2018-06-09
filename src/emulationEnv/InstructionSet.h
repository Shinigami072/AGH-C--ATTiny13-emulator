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
        bool operator () (const Instruction *a, const Instruction *b) const{
            return (*a) < (*b);
        }
    };

    //zawiera wskażniki na instrukjce - umożliwia ich efektywne wyszukiwanie (w przyszłośći)
    class InstructionSet : public std::set<Instruction *,InstructionCompare> {
    public:
        iterator find(uint16_t programInstruction) const{ //TODO: improve search algorithm
            return std::find_if(begin(),end(),[&programInstruction](const Instruction* i){
                return *i==programInstruction;
            });
        }

        void printInstructionList(std::ostream& o){
            for(Instruction* s:*this) //todo: proper instruction listing
                std::cout<<utils::bin16(s->getInstrMask())<<" "<<utils::bin16(s->getInstrVal())<<" "<<s->getMnem()<<" ["<<s->getInstrVal()<<"]"<<std::endl;
        }
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTIONSET_H
