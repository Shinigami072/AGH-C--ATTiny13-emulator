//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_INSTRUCTIONS_H
#define ATTINY13_EMULATOR_INSTRUCTIONS_H
#include "Instruction.h"
#include "NOP.h"
#include "RJMP.h"
#include "../emulationEnv/InstructionSet.h"
#include "INC.h"

namespace emulator{
    /// InstructionSet zawierający wszystkie zaimplementowane instrukcje AVR
    class ATTiny13_InstructionSet: public InstructionSet{
    public:
        ATTiny13_InstructionSet(): InstructionSet(){
            insert(new NOP());
            insert(new RJMP());
            insert(new INC());


            for(Instruction* s:*this) //todo: proper instruction listing
                std::cout<<utils::bin16(s->instrMask)<<" "<<utils::bin16(s->instrVal)<<" "<<s->mnem<<std::endl;
        }
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTIONS_H
