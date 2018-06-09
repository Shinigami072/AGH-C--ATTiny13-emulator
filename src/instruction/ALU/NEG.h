//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_NEG_H
#define ATTINY13_EMULATOR_NEG_H

#include "../Instruction.h"

namespace emulator{
    class NEG: public OneOperand{
    public:
        NEG():OneOperand("1001010ddddd0001","[ALU] NEG"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            //SREG ITHSVNZC
            //H: R3||Rd3
            //V = R==0x80
            //N = R7
            //S = N^V
            //Z = R ==0
            //C = R !=0


            bool H = utils::isSet<3>(at.memory.GP(RdVal));
            if(at.memory.GP(RdVal)!=0x80)
                at.memory.GP(RdVal)=(uint8_t)0-at.memory.GP(RdVal);

            H |= utils::isSet<3>(at.memory.GP(RdVal));
            bool N = utils::isSet<7>(at.memory.GP(RdVal));
            bool Z = at.memory.GP(RdVal)==0;
            bool C = at.memory.GP(RdVal)!=0;
            bool V = at.memory.GP(RdVal)==0x80;
            bool S = N^V;

            at.memory.SREG.setBool(C,0); //C
            at.memory.SREG.setBool(Z,1); //Z
            at.memory.SREG.setBool(N,2); //N
            at.memory.SREG.setBool(V,3); //V
            at.memory.SREG.setBool(S,4); //S
            at.memory.SREG.setBool(H,5); //H


            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_NEG_H
