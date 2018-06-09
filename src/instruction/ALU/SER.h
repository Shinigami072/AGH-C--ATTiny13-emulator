//
// Created by shinigami on 08/06/18.
//

#ifndef ATTINY13_EMULATOR_SER_H
#define ATTINY13_EMULATOR_SER_H

#include "../Instruction.h"

namespace emulator{
    class SER: public OneOperand{
    public:
        SER():OneOperand("11101111dddd1111","[ALU] SER"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u)+16u;


            at.memory.GP(RdVal)=0xFF;

            at.PC++;
        }
    };
};

#endif //ATTINY13_EMULATOR_SER_H
