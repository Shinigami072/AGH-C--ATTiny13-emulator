//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_LDS_H
#define ATTINY13_EMULATOR_LDS_H
#include "../Instruction.h"

namespace emulator{
    class LDS: public OneOperand{
    public:
        LDS():OneOperand("1001000ddddd0000","[MEM]","LDS"){}
        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = static_cast<uint8_t>(static_cast<uint16_t>(instruction&RdMask)>>4u);

            out<<"LDS"<<" "<<utils::getRG_str(RdVal)<<", b'"<<utils::bin16(at.programFlash[PC+1])<<"'"<<std::endl;
        }

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = static_cast<uint8_t>(static_cast<uint16_t>(instruction&RdMask)>>4u);

            at.memory.GP(RdVal)=at.memory[at.programFlash[at.PC+1]];

            at.PC+=2;
        }

        uint8_t length() override {
            return 2;
        }
    };
};
#endif //ATTINY13_EMULATOR_LDS_H
