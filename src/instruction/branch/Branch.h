//
// Created by shinigami on 13/06/18.
//

#ifndef ATTINY13_EMULATOR_BRANCH_H
#define ATTINY13_EMULATOR_BRANCH_H
#include "../Instruction.h"

namespace emulator {
    class BRB : public Instruction {
    public:
        BRB() : Instruction("11110KkkkkkkkKKK", "[BRN]","BRBS/C") {}

        void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto kVal = utils::U2<7>((instruction&kMask)>>3);
            auto KVal = static_cast<uint8_t>((instruction&KMask)&0xF);
            bool B = (instruction&KMask)>7;
            switch(KVal){
                default:
                    out<<"BR"<<utils::getSRAM_FLAG(KVal)<<(!B?"S":"C")<<" "<<short(1+kVal+PC)<<std::endl;
                break;
                case 7:
                    out<<"BR"<<utils::getSRAM_FLAG(KVal)<<(!B?"E":"D")<<" "<<short(1+kVal+PC)<<std::endl;

                break;
            }
        }
        void execute(ATtiny13 &at, uint16_t instruction) const override {
            auto kVal = utils::U2<7>((instruction&kMask)>>3);
            auto KVal = static_cast<uint8_t>((instruction&KMask)&0xF);
            bool B = (instruction&KMask)>7;
            if(at.memory.SREG.getBool(KVal) != B)
                at.PC+=1+kVal;
            else
                at.PC++;
        }
    };

}
#endif //ATTINY13_EMULATOR_BRANCH_H
