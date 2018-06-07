#include <iostream>
#include "ATTinyMemory/ATtiny13.h"
#include "Emulator.h"
#include "hexfile/HexLoader.h"
#include "fstream"
#include "Utils.h"
using namespace emulator;
using namespace hex;
int main() {
    std::ifstream in("Test.hex");
    Hex hex =HexLoader::parse(in);

    size_t i=0;
//    for(uint16_t b:) {
//        std::cout <<bin16(b)<<" ";
//        if((i%8)==7)
//            std::cout << std::endl;
//        i++;
//
//    }
    Emulator tiny;
    tiny.state.flash(hex.toArray16<512>());
    tiny.state.dump(std::cout);
//    tiny.state.programFlash[0]=0xc000;
//    tiny.state.programFlash[2]=0xc001;
//    tiny.state.programFlash[4]=0xc011;
//    tiny.state.programFlash[6]=0xc111;

    i=0;
//    while(tiny.state.PC<tiny.state.programFlash.size()) {
//        std::cout <<std::dec<< i++ << ":" << tiny.state.PC <<" "<< std::hex <<tiny.state.programFlash[tiny.state.PC]<<std::dec<<std::endl;
//        tiny.execute();
//    }
    tiny.state.dump(std::cout);

    return 0;
}