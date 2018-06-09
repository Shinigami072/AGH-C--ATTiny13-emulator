//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_PUSH_POP_H
#define ATTINY13_EMULATOR_PUSH_POP_H
#include "../Instruction.h"

namespace emulator{
    class PUSH: public OneOperand{
    public:
        PUSH():OneOperand("1001001ddddd1111","[MEM] PUSH"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            at.memory.stack.push_back(at.memory.GP(RdVal));
            at.PC++;
        }
    };
    class POP: public OneOperand{
    public:
        POP():OneOperand("1001000ddddd1111","[MEM] POP"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            at.memory.GP(RdVal)=at.memory.stack.pop_back();
            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_PUSH_POP_H
