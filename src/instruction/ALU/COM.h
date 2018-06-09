//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_COM_H
#define ATTINY13_EMULATOR_COM_H

#include "../Instruction.h"

namespace emulator{
    class COM: public OneOperand{
    public:
        COM():OneOperand("1001010ddddd0000","[ALU] COM"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            //SREG ITHSVNZC
            //V = 0
            //N = R7
            //S = N^V <=> N
            //Z = R ==0
            //C = 1



            at.memory.GP(RdVal)=(uint8_t)0xff-at.memory.GP(RdVal);

            bool N = utils::isSet<7>(at.memory.GP(RdVal));
            bool Z = at.memory.GP(RdVal)==0;


            at.memory.SREG.setBool(true,0); //C
            at.memory.SREG.setBool(Z,1); //Z
            at.memory.SREG.setBool(N,2); //N
            at.memory.SREG.setBool(false,3); //V
            at.memory.SREG.setBool(N,4); //S


            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_COM_H
