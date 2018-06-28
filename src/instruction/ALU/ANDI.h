//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_ANDI_H
#define ATTINY13_EMULATOR_ANDI_H

#include "../Instruction.h"

namespace emulator{
    class ANDI: public OneOperand{
    public:
        ANDI():OneOperand("0111KKKKddddKKKK","[ALU]","ANDI ?CBR?"){}

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = static_cast<uint8_t>(uint(instruction&RdMask)>>4u)+16u;

            auto KVal  = static_cast<uint8_t>((instruction&KMask)|((instruction&KMask)>>4u));

            out<<"ANDI"<<" "<<utils::getRG_str(RdVal)<<", b'"<<utils::bin8(KVal)<<"'"<<std::endl;
        }
        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = static_cast<uint8_t>(uint(instruction&RdMask)>>4u)+16u;
            auto KVal  = static_cast<uint8_t>((instruction&KMask)|((instruction&KMask)>>4u));

            //SREG ITHSVNZC
            //V = 0
            //N = R7
            //S = N
            //Z = R ==0

            uint8_t R = at.memory.GP(RdVal)&KVal;

            bool R7  =utils::isSet<7>(R);
            bool N=R7;

            at.memory.SREG.setBool(R ==0,1);//Z
            at.memory.SREG.setBool(N,2);//S
            at.memory.SREG.setBool(N,3);//N
            at.memory.SREG.setBool(false,4);//V

            at.memory.GP(RdVal)=R;
            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_ANDI_H
