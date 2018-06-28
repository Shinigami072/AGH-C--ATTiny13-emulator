//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_AND_H
#define ATTINY13_EMULATOR_AND_H

#include "../Instruction.h"

namespace emulator{
    class AND: public TwoOperand{
    public:
        AND():TwoOperand("001000rdddddrrrr","[ALU]","AND TST"){}

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);
            if(RdVal==RrVal)
                out<<"TST"<<" "<<utils::getRG_str(RdVal)<<std::endl;
            else
                out<<"AND"<<" "<<utils::getRG_str(RdVal)<<","<<utils::getRG_str(RrVal)<<std::endl;
        }
        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);

            //SREG ITHSVNZC
            //V = 0
            //N = R7
            //S = N
            //Z = R ==0

            uint8_t R = at.memory.GP(RdVal)&at.memory.GP(RrVal);

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
#endif //ATTINY13_EMULATOR_AND_H
