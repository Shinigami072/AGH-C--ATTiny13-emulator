//
// Created by shinigami on 13/06/18.
//

#ifndef ATTINY13_EMULATOR_SREG_FLGS_H
#define ATTINY13_EMULATOR_SREG_FLGS_H
#include "../Instruction.h"

namespace emulator {
    class BCLR : public Instruction {
    public:
        BCLR() : Instruction("1001"
                            "0100"
                            "Kkkk"
                            "1000", "[BIT]","CL/SE CZNVSHTI Bset BCLR") {
        }
        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto KVal = static_cast<uint8_t>(instruction&KMask);
            auto kVal = static_cast<uint8_t>((instruction&kMask)>>4u);

            out<<(KVal==0?"SE":"CL")<<utils::getSRAM_FLAG(kVal)<<std::endl;
        }

        void execute(ATtiny13 &at, uint16_t instruction) const override {
            auto KVal = static_cast<uint8_t>(instruction&KMask);
            auto kVal = static_cast<uint8_t>((instruction&kMask)>>4u);
            at.memory.SREG.setBool(KVal==0, kVal);
            at.PC++;
        }
    };
}
#endif //ATTINY13_EMULATOR_SREG_FLGS_H
