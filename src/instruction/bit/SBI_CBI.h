//
// Created by shinigami on 13/06/18.
//

#ifndef ATTINY13_EMULATOR_SBI_CBI_H
#define ATTINY13_EMULATOR_SBI_CBI_H
#include "../Instruction.h"

namespace emulator {
    class SBI : public OneOperand {
    public:
        SBI() : OneOperand("10011010dddddkkk", "[BIT] SBI") {}

        void execute(ATtiny13 &at, uint16_t instruction) const override {

            auto RdVal = uint8_t(uint(instruction & RdMask) >> 3u);
            auto kVal = uint8_t(uint(instruction & kMask));


            at.memory.GP(RdVal) |= 1<<kVal;
            at.PC++;
        }
    };

    class CBI : public OneOperand {
    public:
        CBI() : OneOperand("10011000dddddkkk", "[BIT] CBI") {}

        void execute(ATtiny13 &at, uint16_t instruction) const override {

            auto RdVal = uint8_t(uint(instruction & RdMask) >> 3u);
            auto kVal = uint8_t(uint(instruction & kMask));


            at.memory.GP(RdVal) &= ~(1<<kVal);


            at.PC++;
        }
    };

}
#endif //ATTINY13_EMULATOR_SBI_CBI_H
