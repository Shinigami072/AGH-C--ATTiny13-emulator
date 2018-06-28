//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_INC_H
#define ATTINY13_EMULATOR_INC_H

#include "../Instruction.h"

namespace emulator{
    class INC: public OneOperand{
    public:
        INC():OneOperand("1001010ddddd0011","[ALU]","INC"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = getRegisterRD(instruction);//uint8_t (uint(instruction&RdMask)>>4u);
            //SREG ITHSVNZC
            //V = Rd == 0x7F
            //N = (Rd+1)7
            //S = N^V
            //Z = RD+1 ==0
            bool V = at.memory.GP(RdVal)==0x7F;

            at.memory.GP(RdVal)++;
            bool N = utils::isSet<7>(at.memory.GP(RdVal));
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
#endif //ATTINY13_EMULATOR_INC_H
