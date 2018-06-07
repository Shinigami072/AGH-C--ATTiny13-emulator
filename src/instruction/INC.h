//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_INC_H
#define ATTINY13_EMULATOR_INC_H

#include "Instruction.h"

namespace emulator{
    class INC: public OneOperand{
    public:
        INC():OneOperand("1001010ddddd0011","INC"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            bool V = at.memory.GP(RdVal)==0x7F;
            //SREG ITHSVNZC
            //V = Rd == 0x7F
            //N = (Rd+1)7
            //S = N^V
            //Z = RD+1 ==0

            at.memory.GP(RdVal)++;
            bool N = (at.memory.GP(RdVal)&(1u<<7u))!=0;
            bool Z = at.memory.GP(RdVal)==0;
            bool S = N^V;
            at.memory.SREG=(uint8_t)(
                    uint8_t (at.memory.SREG&((uint8_t)0x1E))|
                    S?(1u<<4u):0u|
                    V?(1u<<3u):0u|
                    N?(1u<<2u):0u|
                    Z?(1u<<1u):0u);

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_INC_H
