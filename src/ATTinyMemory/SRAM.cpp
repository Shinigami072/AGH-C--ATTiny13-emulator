//
// Created by shinigami on 07/06/18.
//

#include "SRAM.h"

void emulator::SRAMmemory::dump(std::ostream &o) {
    o<<"memory:"<<std::endl;
    int pc=0;
    for(uint8_t i:data){
        o<<utils::bin8(i)<<" ";
        if((++pc)%8==0)
            o<<std::endl;
    }
}
