//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_SRAM_H
#define ATTINY13_EMULATOR_SRAM_H

#include <array>
#include "../Utils.h"

namespace emulator {
    class SRAMmemory {
    protected:
        std::array<uint8_t, 32+64+64> data;
    public:
        uint8_t& SPL,SREG;
        SRAMmemory():SPL(data[0x3d]),SREG(data[0x3f]){
            std::fill(data.begin(),data.end(),0);
            SPL=0x9f;
        }
        uint8_t& IO(char c){
            if(c>=0 && c<0x40) //todo: write protection
                operator[](c+(char)0x20);
        }
        uint8_t& GP(char c){
            if(c>=0 && c<0x20)
                operator[](c);
        }
        uint8_t& SRAM(char c){
            if(c>=0&&c<0x20)
                operator[](c+(char)0x60);
        }
        uint8_t& operator[] (char c){
            return data[c];
        }
        void dump(std::ostream &o);


    };

}
#endif //ATTINY13_EMULATOR_SRAM_H
