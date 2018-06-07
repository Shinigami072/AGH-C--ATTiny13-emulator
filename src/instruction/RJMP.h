//
// Created by shinigami on 01/06/18.
//

#ifndef ATTINY13_EMULATOR_RJMP_H
#define ATTINY13_EMULATOR_RJMP_H
#include "Instruction.h"
#include "../Utils.h"
namespace emulator{
    class RJMP: public Instruction {
        int16_t kval_table[];
    public:
        RJMP():Instruction("1100kkkkkkkkkkkk","RJMP"){}

        void execute(ATtiny13& at,uint16_t instruction) const override{
            std::cout<<hex::bin16(instruction&kMask)<<hex::U2<12>(instruction&kMask)<<std::endl;

            at.PC+=hex::U2<12>(instruction&kMask);
        }
    };
}


#endif //ATTINY13_EMULATOR_RJMP_H
