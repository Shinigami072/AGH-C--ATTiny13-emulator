//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_INSTRUCTIONS_H
#define ATTINY13_EMULATOR_INSTRUCTIONS_H
#include "instruction/Instruction.h"
#include "instruction/NOP.h"
#include "instruction/RJMP.h"
#include "instruction/InstructionSet.h"
namespace emulator{
    class ATTiny13_InstructionSet: public InstructionSet{
    public:
        ATTiny13_InstructionSet(): InstructionSet(){
            insert(new NOP());
            insert(new RJMP());
            for(Instruction* s:*this) //todo: protper instruction listing
                std::cout<<hex::bin16(s->instrMask)<<" "<<hex::bin16(s->instrVal)<<" "<<s->mnem<<std::endl;
        }
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTIONS_H
