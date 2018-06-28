//
// Created by shinigami on 07/06/18.
//

#include "SRAM.h"

void emulator::SRAMmemory::dump(std::ostream &o) const{
    o<<"SP: "<<static_cast<short>(SPL)<<std::endl;

    o<<"SREG: ";
    for(int i=0;i<7;i++)
        if(SREG.getBool(i))
            o<<utils::getSRAM_FLAG(i);
        else
            o<<'-';
    o<<std::endl;

    o<<"registers:"<<std::endl;
    for(int i=0;i<32;i++)
        o<<utils::getRG_str(i)<<": "<<static_cast<short>(GP(i))<<std::endl;

    o<<"X: "<< X.operator uint16_t()<<std::endl;
    o<<"Y: "<< Y.operator uint16_t()<<std::endl;
    o<<"Z: "<< Z.operator uint16_t()<<std::endl;
    o<<std::endl;

    o<<"memory:"<<std::endl;
    int pc=0;
    for(uint8_t i:data){
        o<<utils::bin8(i)<<" ";

        if((++pc)%8==0)
            o<<std::endl;
    }
}

void emulator::SRAMmemory::flash(const std::array<uint8_t, 160>& array) {
    std::move(array.begin(),array.end(),data.begin());
}

void emulator::RegisterFlagAdapter::setBool(bool b, int i) {
    if(i<0||i>=8)
        throw register_out_of_range("Error acessing bit"+i);

    if(b)
        _register|=1<<(i%8);
    else
        _register&=~(1<<(i%8));

}

bool emulator::RegisterFlagAdapter::getBool(int i) const {
    if(i<0||i>=8)
        throw register_out_of_range("Error acessing bit"+i);

    return (_register&(1u<<(i%8)))!=0;

}
