//
// Created by shinigami on 13/06/18.
//

#ifndef ATTINY13_EMULATOR_BST_BLD_H
#define ATTINY13_EMULATOR_BST_BLD_H
#include "../Instruction.h"

namespace emulator {
    class BST : public OneOperand {
    public:
        BST() : OneOperand("1111101ddddd0kkk", "[BIT]","BST") {}

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            auto kVal = uint8_t(uint(instruction & kMask));


            out<<getMnem()<<" "<<utils::getRG_str(RdVal)<<","<<short(kVal)<<std::endl;
        }

        void execute(ATtiny13 &at, uint16_t instruction) const override {

            auto RdVal = uint8_t(uint(instruction & RdMask) >> 4u);
            auto kVal = uint8_t(uint(instruction & kMask));


            bool T = (at.memory.GP(RdVal) & 1<<kVal)!=0;
            at.memory.SREG.setBool(T,6);

            at.PC++;
        }
    };

    class BLD : public OneOperand {
    public:

        BLD() : OneOperand("1111100ddddd0kkk", "[BIT]","BLD") {}
        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            auto kVal = static_cast<uint8_t>(uint(instruction & kMask));

            out<<getMnem()<<" "<<utils::getRG_str(RdVal)<<","<<short(kVal)<<std::endl;
        }
        void execute(ATtiny13 &at, uint16_t instruction) const override {

            auto RdVal = static_cast<uint8_t>(uint(instruction & RdMask) >> 4u);
            auto kVal = static_cast<uint8_t>(uint(instruction & kMask));


            bool T = at.memory.SREG.getBool(6);
            if(T)
                at.memory.GP(RdVal)|=1<<kVal;
            at.PC++;
        }
    };
}
#endif //ATTINY13_EMULATOR_BST_BLD_H
