//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_SBR_H
#define ATTINY13_EMULATOR_SBR_H

#include "../Instruction.h"

namespace emulator{
    class SBR: public OneOperand{
    public:
        SBR():OneOperand("0110KKKKddddKKKK","[ALU] SBR"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u)+16u;
            auto KVal = uint8_t (uint(instruction&KMask)>>4u)|instruction&KMask;


            at.memory.GP(RdVal)|=KVal;

            //SREG ITHSVNZC
            //V = 0
            //N = R7
            //S = V^N
            //Z = R==0
            at.memory.SREG.setBool(at.memory.GP(RdVal)==0,1);//Z
            at.memory.SREG.setBool(utils::isSet<7>(at.memory.GP(RdVal)),2);//N
            at.memory.SREG.setBool(false,3);//V
            at.memory.SREG.setBool(at.memory.SREG.getBool(2),4);//S

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_SBR_H
