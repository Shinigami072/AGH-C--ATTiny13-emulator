//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_LDI_H
#define ATTINY13_EMULATOR_LDI_H
#include "../Instruction.h"

namespace emulator{
    class LDI: public OneOperand{
    public:
        LDI():OneOperand("1110KKKKddddKKKK","[MEM]","LDI SER"){}

        void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = static_cast<uint8_t>(static_cast<uint>(instruction&RdMask)>>4u)+16u;
            auto KVal  = static_cast<uint8_t>((instruction&KMask)|((instruction&KMask)>>4u));
            if(KVal != 0xFF)
                out<<"LDI"<<" "<<utils::getRG_str(RdVal)<<", b'"<<utils::bin8(KVal)<<"'"<<std::endl;
            else
                out<<"SER"<<" "<<utils::getRG_str(RdVal)<<std::endl;

        }
        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = static_cast<uint8_t>((static_cast<uint>(instruction&RdMask)>>4u)+16u);
            auto KVal = static_cast<uint8_t>(instruction&KMask)|static_cast<uint8_t>((instruction&KMask)>>4u);

            at.memory.GP(RdVal)=KVal;

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_LDI_H
