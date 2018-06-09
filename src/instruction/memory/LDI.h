//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_LDI_H
#define ATTINY13_EMULATOR_LDI_H
#include "../Instruction.h"

namespace emulator{
    class LDI: public OneOperand{
    public:
        LDI():OneOperand("1110KKKKddddKKKK","[MEM] LDI"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u)+16u;
            auto KVal = uint8_t(instruction&KMask)|uint8_t((instruction&KMask)>>4u);

            at.memory.GP(RdVal)=KVal;

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_LDI_H
