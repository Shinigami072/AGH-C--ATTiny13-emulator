//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_INSTRUCTIONS_H
#define ATTINY13_EMULATOR_INSTRUCTIONS_H
#include "Instruction.h"
#include "NOP.h"
#include "RJMP.h"
#include "../emulationEnv/InstructionSet.h"
#include "ALU/INC.h"
#include "ALU/DEC.h"
#include "ALU/SER.h"
#include "ALU/CLR.h"
#include "ALU/ADD.h"
#include "ALU/SUB.h"
#include "ALU/TST.h"
#include "ALU/SBR.h"
#include "ALU/NEG.h"
#include "ALU/COM.h"

namespace emulator{
    /// InstructionSet zawierający wszystkie zaimplementowane instrukcje AVR
    class ATTiny13_InstructionSet: public InstructionSet{
    public:
        ATTiny13_InstructionSet(): InstructionSet(){
            //basic - test
            insert(new NOP());
            insert(new RJMP());

            //ALU
                //basic +-1
                insert(new INC());
                insert(new DEC());
                //set.clr registers
                insert(new SBR());
                insert(new SER());
                insert(new CLR());
                insert(new TST());

                //negation
                insert(new NEG());
                insert(new COM());

                //+- registers
                insert(new ADD());
                insert(new SUB());


            for(Instruction* s:*this) //todo: proper instruction listing
                std::cout<<utils::bin16(s->instrMask)<<" "<<utils::bin16(s->instrVal)<<" "<<s->mnem<<std::endl;
        }
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTIONS_H
