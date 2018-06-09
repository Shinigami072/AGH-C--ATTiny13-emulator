//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_TST_H
#define ATTINY13_EMULATOR_TST_H

#include "../Instruction.h"

namespace emulator{
    class TST: public OneOperand{
    public:
        TST():OneOperand("001001dddddddddd","[ALU] TST"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u)&0x1f;


            at.memory.GP(RdVal)&=at.memory.GP(RdVal);

            //SREG ITHSVNZC
            //V = 0
            //N = R7
            //S = N^V <=> !N
            //Z = R ==0
            at.memory.SREG.setBool(at.memory.GP(RdVal) == 0,1);//Z
            at.memory.SREG.setBool(true,2);//N
            at.memory.SREG.setBool(!utils::isSet<7>(at.memory.GP(RdVal)),3);//V
            at.memory.SREG.setBool( at.memory.SREG.getBool(3),4);//S

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_TST_H
