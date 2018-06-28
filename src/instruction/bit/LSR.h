//
// Created by shinigami on 13/06/18.
//

#ifndef ATTINY13_EMULATOR_LSL_LSR_H
#define ATTINY13_EMULATOR_LSL_LSR_H
#include "../Instruction.h"

namespace emulator{
    class LSR: public OneOperand{
    public:
        LSR():OneOperand("1001010ddddd0110","[BIT]","LSR"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{

            auto RdVal = static_cast<uint8_t> (uint(instruction&RdMask)>>4u);
            uint8_t rd = at.memory.GP(RdVal);
            bool C = (at.memory.GP(RdVal)&1) !=0;

            //SREG ITHSVNZC
            //V =N^C= !C
            //N = 0
            //S = N^V = !V =C
            //Z = R ==0
            //C = RD0

            at.memory.GP(RdVal)>>=1;

            at.memory.SREG.setBool(C,0);//C
            at.memory.SREG.setBool(at.memory.GP(RdVal)==0,1);//Z
            at.memory.SREG.setBool(false,2);//N
            at.memory.SREG.setBool(!C,0);//V
            at.memory.SREG.setBool(C,0);//S

            at.PC++;
        }
    };

    class ROR: public OneOperand{
    public:
        ROR():OneOperand("1001010ddddd0111","[BIT]","ROR"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{

            auto RdVal = static_cast<uint8_t> (uint(instruction&RdMask)>>4u);
            uint8_t rd = at.memory.GP(RdVal);
            bool C = (at.memory.GP(RdVal)&1) !=0;

            //SREG ITHSVNZC
            //V =N^C= !C
            //N = 0
            //S = N^V = !V =C
            //Z = R ==0
            //C = RD0

            at.memory.GP(RdVal)>>=1;

            if(at.memory.SREG.getBool(0))//C
                at.memory.GP(RdVal)|=(1<<7);


            at.memory.SREG.setBool(C,0);//C
            at.memory.SREG.setBool(at.memory.GP(RdVal)==0,1);//Z
            at.memory.SREG.setBool(false,2);//N
            at.memory.SREG.setBool(!C,0);//V
            at.memory.SREG.setBool(C,0);//S

            at.PC++;
        }
    };
};

#endif //ATTINY13_EMULATOR_LSL_LSR_H
