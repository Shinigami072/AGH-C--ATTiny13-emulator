//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_NOP_H
#define ATTINY13_EMULATOR_NOP_H

#include "Instruction.h"
namespace emulator {

    //pusta operacja
    class NOP : public Instruction {
    public:
        NOP(): Instruction("0000000000000000","[   ]","NOP"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            at.PC++;
        }
    };



}
#endif //ATTINY13_EMULATOR_NOP_H
