//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_LDS_H
#define ATTINY13_EMULATOR_LDS_H
#include "../Instruction.h"

namespace emulator{
    class LDS: public OneOperand{
    public:
        LDS():OneOperand("1001000ddddd0000","[MEM] LDS"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);

            at.memory.GP(RdVal)=at.memory[at.programFlash[at.PC+1]];

            at.PC+=2;
        }
    };
};
#endif //ATTINY13_EMULATOR_LDS_H
