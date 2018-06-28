//
// Created by shinigami on 10/06/18.
//

#ifndef ATTINY13_EMULATOR_CP_H
#define ATTINY13_EMULATOR_CP_H
#include "../Instruction.h"

namespace emulator{
    class CP: public TwoOperand{
    public:
        CP():TwoOperand("000k01rdddddrrrr","[BRN]","CP CPC"){}

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);

            out<<(((instruction&kMask) == 0)?"CPC ":"CP  ")<<" "<<utils::getRG_str(RdVal)<<","<<utils::getRG_str(RrVal)<<std::endl;

        }

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);

            //SREG ITHSVNZC
            //H = ((!RD3&&RR3) || (RR3&&R3) || (R3&&!RD3))
            //S = N^V
            //V = (RD7&&!RR7&&!R7) || (!RD7&&RR7&&R7)
            //N = R7
            //Z = R ==0
            //C = (!RD7&&RR7) || (RR7&&R7) || (R7 && !RD7)

            uint8_t R = at.memory.GP(RdVal)-at.memory.GP(RrVal);
            if((instruction&kMask) == 0)
            if(at.memory.SREG.getBool(0)){//C
                R-=1;
            }

            bool RD3 =utils::isSet<3>(at.memory.GP(RdVal)),
            RR3 =utils::isSet<3>(at.memory.GP(RrVal)),
            R3 =utils::isSet<3>(R),
            RD7 =utils::isSet<7>(at.memory.GP(RdVal)),
            RR7 =utils::isSet<7>(at.memory.GP(RrVal)),
            R7  =utils::isSet<7>(R);

            bool N=R7,
                    V=(RD7&&!RR7&&!R7) || (!RD7&&RR7&&R7);
            at.memory.SREG.setBool( (!RD7&&RR7) || (RR7&&R7) || (R7 && !RD7),0);//C
            at.memory.SREG.setBool(R ==0,1);//Z
            at.memory.SREG.setBool(N,2);//N
            at.memory.SREG.setBool(V,3);//V
            at.memory.SREG.setBool(N^V,4);//S
            at.memory.SREG.setBool(((!RD3&&RR3) || (RR3&&R3) || (R3&&!RD3)),5);//H

            at.PC++;
        }
    };
};

#endif //ATTINY13_EMULATOR_CP_H
