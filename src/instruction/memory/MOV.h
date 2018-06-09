//
// Created by shinigami on 09/06/18.
//

#ifndef ATTINY13_EMULATOR_MOV_H
#define ATTINY13_EMULATOR_MOV_H

#include "../Instruction.h"

namespace emulator{
    class MOV: public TwoOperand{
    public:
        MOV():TwoOperand("001011rdddddrrrr","[MEM] MOV"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            auto RrVal = utils::isSet<9>(instruction&RrMask)?uint8_t(instruction&RrMask^(1u<<10)|(1u<<4)):uint8_t(instruction&RrMask);


            at.memory.GP(RdVal)=at.memory.GP(RrVal);

            at.PC++;
        }
    };
};

#endif //ATTINY13_EMULATOR_MOV_H
