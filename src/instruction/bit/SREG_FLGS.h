//
// Created by shinigami on 13/06/18.
//

#ifndef ATTINY13_EMULATOR_SREG_FLGS_H
#define ATTINY13_EMULATOR_SREG_FLGS_H
#include "../Instruction.h"

namespace emulator {
    class SREG_FLAGS : public Instruction {
    public:
        SREG_FLAGS() : Instruction("1001"
                            "0100"
                            "Kkkk"
                            "1000", "[BIT] CL/SE CZNVSHTI") {
        }
        void execute(ATtiny13 &at, uint16_t instruction) const override {
            auto KVal = uint8_t (instruction&KMask);
            auto kVal = uint8_t((instruction&kMask)>>4u);
            at.memory.SREG.setBool(KVal==0, kVal);
            at.PC++;
        }
    };
}
#endif //ATTINY13_EMULATOR_SREG_FLGS_H
