//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_DEC_H
#define ATTINY13_EMULATOR_DEC_H

#include "../Instruction.h"

namespace emulator{
    class DEC: public OneOperand{
    public:
        DEC():OneOperand("1001010ddddd1010","[ALU] DEC"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            bool V = at.memory.GP(RdVal)==0x80;
            //SREG ITHSVNZC
            //V = Rd == 0x80
            //N = (Rd-1)7
            //S = N^V
            //Z = RD-1 ==0

            at.memory.GP(RdVal)--;

            bool N = (at.memory.GP(RdVal)&(1u<<7u))!=0;
            bool Z = at.memory.GP(RdVal)==0;
            bool S = N^V;

            at.memory.SREG.setBool(Z,1);
            at.memory.SREG.setBool(N,2);
            at.memory.SREG.setBool(V,3);
            at.memory.SREG.setBool(S,4);

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_DEC_H
