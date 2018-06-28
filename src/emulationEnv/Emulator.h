//
// Created by shinigami on 01/06/18.
//

#ifndef ATTINY13_EMULATOR_EMULATOR_H
#define ATTINY13_EMULATOR_EMULATOR_H

#include "../ATTinyMemory/ATtiny13.h"
#include <algorithm>
#include "../instruction/Instructions.h"
#include <ostream>

namespace emulator {
    class Emulator{
    public:
        class unexpected_instruction: public std::runtime_error{
            public:
            uint16_t instruction;
            unexpected_instruction(const char* s,uint16_t instr):runtime_error(s),instruction(instr){}
        };
        Emulator();
        //todo: modify state
        ~Emulator()=default;

        ///Execute Current instruction
        void execute(std::ostream* o=nullptr);

        InstructionSet instructionSet;

        ATtiny13 state; //todo: add abstraction layer - allowing for different mircocontollers
        void dissasemble(std::ostream &ostream);
    };
}

#endif //ATTINY13_EMULATOR_EMULATOR_H
