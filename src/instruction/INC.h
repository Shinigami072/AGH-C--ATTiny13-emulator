//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_INC_H
#define ATTINY13_EMULATOR_INC_H

#include "Instruction.h"

namespace emulator{
    class INC: public OneOperand{
        INC():OneOperand("1001010ddddd0011","INC"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            std::cout<<hex::bin16(instruction&RdMask)<<((instruction&RdMask)>>4)<<std::endl;

            at.PC++;
        }
    };
};
#endif //ATTINY13_EMULATOR_INC_H
