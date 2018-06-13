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

void emulator::RegisterFlagAdapter::setBool(bool b, int i) {
    if(i<0||i>=8)
        register_out_of_range("Error acessing bit"+i);

    if(b)
        _register|=1<<(i%8);
    else
        _register&=~(1<<(i%8));

}

bool emulator::RegisterFlagAdapter::getBool(int i) const {
    if(i<0||i>=8)
        register_out_of_range("Error acessing bit"+i);

    return (_register&(1u<<(i%8)))!=0;

}
