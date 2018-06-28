//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_ATTINY_H
#define ATTINY13_EMULATOR_ATTINY_H

#include <array>
#include <iostream>
#include "SRAM.h"


namespace emulator {

    class ATtiny13 {
    public:
        ATtiny13();

        ~ATtiny13()=default;


        void flash(const std::array<uint16_t, 512> &programFlash);

        void dump(std::ostream &o)const;

        std::array<uint16_t, 512> programFlash;
        SRAMmemory memory;
        uint16_t PC;

    };


}

#endif //ATTINY13_EMULATOR_ATTINY_H
