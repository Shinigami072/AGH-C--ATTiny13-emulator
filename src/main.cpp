#include <iostream>
#include "ATTinyMemory/ATtiny13.h"
#include "emulationEnv/Emulator.h"
#include "hexfile/HexLoader.h"
#include "fstream"
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for;

using namespace emulator;
using namespace utils;

//todo: loadfile
//todo: interpret arguments
//todo: allow step-by step execution
//todo: allow timed execution
int main(int argc,char** argv) {
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
    while(tiny.state.PC<tiny.state.programFlash.size()) {
        std::cout <<std::dec<< i++ << ":" << tiny.state.PC <<" "<<utils::bin16(tiny.state.programFlash[tiny.state.PC])<<std::endl;
        tiny.execute();
        if(i%20==0)
            tiny.state.memory.dump(std::cout);
        std::this_thread::sleep_for(std::chrono::milliseconds{500});
    }
    tiny.state.dump(std::cout);

    return 0;
}