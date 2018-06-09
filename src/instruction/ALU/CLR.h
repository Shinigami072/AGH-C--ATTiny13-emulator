
//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_CLR_H
#define ATTINY13_EMULATOR_CLR_H

#include "../Instruction.h"

namespace emulator{
    class CLR: public OneOperand{
    public:
        CLR():OneOperand("001001dddddddddd","[ALU] CLR"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u)&0x1f;


            at.memory.GP(RdVal)^=at.memory.GP(RdVal);

            //SREG ITHSVNZC
            //V = 0
            //N = 0
            //S = 0
            //Z = 1
            at.memory.SREG.setBool(true,1);
            at.memory.SREG.setBool(false,2);
            at.memory.SREG.setBool(false,3);
            at.memory.SREG.setBool(false,4);

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_CRL_H
