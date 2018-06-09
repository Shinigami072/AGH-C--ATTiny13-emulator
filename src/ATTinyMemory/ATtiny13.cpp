//
// Created by shinigami on 31/05/18.
//
#include "../instruction/Instructions.h"

namespace emulator {

    ATtiny13::ATtiny13() : PC(0),programFlash(), memory() {
    }

    ///zrzut pamięci do tekstu - human readable
    //todo: zapis do pliku
    void ATtiny13::dump(std::ostream &o) const{
        o<<"PC: "<<PC<<std::endl;
        o<<"ProgramFlash:"<<std::endl;
        uint16_t pc=0;

        for(uint16_t i:programFlash){
            o<<utils::bin16(i)<<" ";
            if((++pc)%4==0)
                o<<std::endl;
        }

        o<<std::endl;
        memory.dump(o);
    }

    ///zapis programu do pamięci witrualnego attiny
    void ATtiny13::flash(const std::array<uint16_t, 512> &pF) {
            std::copy(pF.begin(),pF.end(),programFlash.begin());
    }
}

