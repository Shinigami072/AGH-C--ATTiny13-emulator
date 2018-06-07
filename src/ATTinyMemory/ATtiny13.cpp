//
// Created by shinigami on 31/05/18.
//
#include "../Instructions.h"
#include "ATtiny13.h"
#include "../Utils.h"

namespace emulator {

    ATtiny13::ATtiny13() : PC(0),programFlash(), memory() {
    }

    void ATtiny13::dump(std::ostream &o) {
        o<<"PC: "<<PC<<std::endl;
        o<<"ProgramFlash:"<<std::endl;
        uint16_t pc=0;

        for(uint16_t i:programFlash){
            o<<hex::bin16(i)<<" ";
            if((++pc)%4==0)
                o<<std::endl;
        }

        o<<std::endl;
        memory.dump(o);
    }

    void ATtiny13::flash(const std::array<uint16_t, 512> &pF) {
            std::copy(pF.begin(),pF.end(),programFlash.begin());
    }
}

