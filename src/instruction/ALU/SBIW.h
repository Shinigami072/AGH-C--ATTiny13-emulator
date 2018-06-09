//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_SBIW_H
#define ATTINY13_EMULATOR_SBIW_H
#include "../Instruction.h"

namespace emulator{
    class SBIW: public OneOperand{
    public:
        SBIW():OneOperand("10010111KKddKKKK","[ALU] SBIW"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (2*(uint(instruction&RdMask)>>4u)+24u);
            auto KVal  = uint8_t (instruction&KMask|(instruction&KMask>>2u));

            //SREG ITHSVNZC
            //V = !R15&&Rdh7
            //N = R15
            //S = N^V
            //Z = R ==0
            //C = R15&&!Rdh7
            uint16_t Rd = (at.memory.GP(RdVal+uint8_t(1))<<8u)|at.memory.GP(RdVal);
            uint16_t R = Rd-KVal;

            bool
                    Rdh7 =utils::isSet<7>(at.memory.GP(RdVal)),
                    R15  =utils::isSet<15>(R);

            bool N=R15, V=!R15&&Rdh7;
            at.memory.SREG.setBool(R15&&!Rdh7,0);//C
            at.memory.SREG.setBool(R ==0,1);//Z
            at.memory.SREG.setBool(N^V,2);//S
            at.memory.SREG.setBool(N,3);//N
            at.memory.SREG.setBool(V,4);//V
            at.memory.GP(RdVal)=uint8_t(R>>8u&(uint8_t)0xff);
            at.memory.GP(RdVal+(uint8_t)1)=uint8_t(R&(uint8_t)0xff);

            at.PC++;
        }
    };
};

#endif //ATTINY13_EMULATOR_SBIW_H
