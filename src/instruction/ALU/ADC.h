//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_ADC_H
#define ATTINY13_EMULATOR_ADC_H

#include "../Instruction.h"

namespace emulator{
    class ADC: public TwoOperand{
    public:
        ADC():TwoOperand("000111rdddddrrrr","[ALU]","ADC [BIT] ROL"){}

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);
            if(RdVal==RrVal)
                out<<"ROL"<<" "<<utils::getRG_str(RdVal)<<std::endl;
            else
                out<<"ADC"<<" "<<utils::getRG_str(RdVal)<<","<<utils::getRG_str(RrVal)<<std::endl;
        }
        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);
            //SREG ITHSVNZC
            //H = ((RD3&&RR3) || (RR3&&!R3) || (!R3&&RD3))
            //V = (RD7&&RR7&&!R7) || (!RD7&&!RR7&&R7)
            //N = R7
            //S = N^V
            //Z = R ==0
            //C = (RD7&&RR7) || (RR7&&!R7) || (!R7 && RD7)

            uint8_t R = at.memory.GP(RdVal)+at.memory.GP(RrVal)+uint8_t(at.memory.SREG.getBool()?1u:0u);

            bool
                    RD3 =utils::isSet<3>(at.memory.GP(RdVal)),
                    RR3 =utils::isSet<3>(at.memory.GP(RrVal)),
                    R3 =utils::isSet<3>(R),
                    RD7 =utils::isSet<7>(at.memory.GP(RdVal)),
                    RR7 =utils::isSet<7>(at.memory.GP(RrVal)),
                    R7  =utils::isSet<7>(R);
            bool N=R7,
                    V=(RD7&&RR7&&!R7) || (!RD7&&!RR7&&R7);
            at.memory.SREG.setBool((RD7&&RR7) || (RR7&&!R7) || (!R7 && RD7),0);//C
            at.memory.SREG.setBool(R ==0,1);//Z
            at.memory.SREG.setBool(N^V,2);//S
            at.memory.SREG.setBool(N,3);//N
            at.memory.SREG.setBool(V,4);//V
            at.memory.SREG.setBool(((RD3&&RR3) || (RR3&&!R3) || (!R3&&RD3)),5);//H
            at.memory.GP(RdVal)=R;
            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_ADC_H
