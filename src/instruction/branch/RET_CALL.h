//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_RET_CALL_H
#define ATTINY13_EMULATOR_RET_CALL_H
#include "../Instruction.h"

namespace emulator {
    class RET : public Instruction {
    public:
        RET() : Instruction("1001010100001000", "[BRN] RET") {}

        void execute(ATtiny13 &at, uint16_t instruction) const override {
            at.PC = at.memory.stack.pop_back16();
        }
    };
    class RCALL : public Instruction {
    public:
        RCALL() : Instruction("1101kkkkkkkkkkkk", "[BRN] RCALL") {}

        void execute(ATtiny13 &at, uint16_t instruction) const override {
            at.memory.stack.push_back(uint16_t(at.PC+1));
            at.PC+=1+utils::U2<12>(instruction&kMask);
        }
    };
}
#endif //ATTINY13_EMULATOR_RET_CALL_H
