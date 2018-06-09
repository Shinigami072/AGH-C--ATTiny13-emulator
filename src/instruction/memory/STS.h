//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_STS_H
#define ATTINY13_EMULATOR_STS_H
#include "../Instruction.h"

namespace emulator{
    class STS: public OneOperand{
    public:
        STS():OneOperand("1001001ddddd0000","[MEM] STS"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);

            at.memory[at.programFlash[at.PC+1]]=at.memory.GP(RdVal);

            at.PC+=2;
        }
    };
};
#endif //ATTINY13_EMULATOR_STS_H
