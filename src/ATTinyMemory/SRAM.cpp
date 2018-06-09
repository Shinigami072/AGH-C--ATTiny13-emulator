//
// Created by shinigami on 07/06/18.
//

#include "SRAM.h"

void emulator::SRAMmemory::dump(std::ostream &o) const{
    o<<"memory:"<<std::endl;
    int pc=0;
    for(uint8_t i:data){
        if(pc%8==0)
            o<<utils::bin16(pc)<<": ";

        o<<utils::bin8(i)<<" ";

        if((++pc)%8==0)
            o<<std::endl;
    }
}
