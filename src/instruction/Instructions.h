//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_INSTRUCTIONS_H
#define ATTINY13_EMULATOR_INSTRUCTIONS_H
#include "Instruction.h"
#include "NOP.h"
#include "branch/RJMP.h"
#include "../emulationEnv/InstructionSet.h"
#include "ALU/INC.h"
#include "ALU/DEC.h"
#include "ALU/SER.h"
#include "ALU/ADD.h"
#include "ALU/SUB.h"
#include "ALU/NEG.h"
#include "ALU/COM.h"
#include "ALU/AND.h"
#include "ALU/ANDI.h"
#include "ALU/ORI.h"
#include "ALU/OR.h"
#include "ALU/EOR.h"
#include "ALU/ADC.h"
#include "ALU/SUBI.h"
#include "ALU/SBC.h"
#include "ALU/SBCI.h"
#include "ALU/ADIW.h"
#include "ALU/SBIW.h"
#include "memory/PUSH_POP.h"
#include "branch/RET_CALL.h"
#include "memory/LDS.h"
#include "memory/LDI.h"
#include "memory/MOV.h"
#include "memory/STS.h"
#include "bit/LSR.h"
#include "bit/SBI_CBI.h"
#include "bit/BST_BLD.h"

namespace emulator{
    /// InstructionSet zawierający wszystkie zaimplementowane instrukcje AVR
    class ATTiny13_InstructionSet: public InstructionSet{
    public:
        ATTiny13_InstructionSet(): InstructionSet(){
            //basic - test
            insert(new NOP());

            //ALU
                //basic +-1
                insert(new INC());
                insert(new DEC());

                //logic
                insert(new ANDI());//CBR
                insert(new AND());
                insert(new ORI());
                insert(new OR());
                insert(new EOR());


                //set.clr registers
                insert(new SER());

                //negation
                insert(new NEG());
                insert(new COM());

                //+ registers
                insert(new ADD());
                insert(new ADC());

                //-registers
                insert(new SUB());
                insert(new SUBI());
                //-carry
                insert(new SBC());
                insert(new SBCI());

                //+- words
                insert(new ADIW());
                insert(new SBIW());

            //memory
                insert(new PUSH());
                insert(new POP());
                insert(new MOV());
                insert(new LDI());
                insert(new LDS());
                insert(new STS());


            //branch
                insert(new RJMP());
                insert(new RET());
                insert(new RCALL());
            //bit

                insert(new LSR());
                insert(new ROR());
                insert(new SBI());
                insert(new CBI());
                insert(new BST());
                insert(new BLD());

        }
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTIONS_H
