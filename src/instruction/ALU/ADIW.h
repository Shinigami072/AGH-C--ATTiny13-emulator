//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_ADIW_H
#define ATTINY13_EMULATOR_ADIW_H
#include "../Instruction.h"

namespace emulator{
    class ADIW: public OneOperand{
    public:
        ADIW():OneOperand("10010110KKddKKKK","[ALU]","ADIW"){}

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = static_cast<uint8_t>(2*(uint(instruction&RdMask)>>4u)+24u);
            auto KVal  = static_cast<uint8_t>(instruction&(KMask&0xf))|(((instruction&KMask)>>2)&0xF0);

            out<<"ADIW"<<" "<<utils::getRG_str(RdVal)<<", "<<short(KVal)<<std::endl;
        }

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = static_cast<uint8_t>(2*(uint(instruction&RdMask)>>4u)+24u);
            auto KVal  = static_cast<uint8_t>(instruction&(KMask&0xf))|(((instruction&KMask)>>2)&0xF0);

            //SREG ITHSVNZC
            //V = R15&&!Rdh7
            //N = R15
            //S = N^V
            //Z = R ==0
            //C = !R15&&Rdh7
            int16_t Rd = (at.memory.GP(RdVal+uint8_t(1))<<8u)|at.memory.GP(RdVal);
            int16_t R = Rd+KVal;

            bool
                    Rdh7 =utils::isSet<7>(at.memory.GP(RdVal)),
                    R15  =utils::isSet<15>(R);

            bool N=R15, V=R15&&!Rdh7;
            at.memory.SREG.setBool(!R15&&Rdh7,0);//C
            at.memory.SREG.setBool(R ==0,1);//Z
            at.memory.SREG.setBool(N^V,2);//S
            at.memory.SREG.setBool(N,3);//N
            at.memory.SREG.setBool(V,4);//V
            at.memory.GP(RdVal+1)=uint8_t(R>>8u&(uint8_t)0xff);
            at.memory.GP(RdVal)=uint8_t(R&(uint8_t)0xff);

            at.PC++;
        }
    };
};

#endif //ATTINY13_EMULATOR_ADIW_H
