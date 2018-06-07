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
            ///idea: referencje do nazwanych rejestrów
            uint8_t& SPL,SREG;

            SRAMmemory():data(),SPL(data[0x3d]),SREG(data[0x3f]){
                std::fill(data.begin(),data.end(),0);
                SPL=0x9f;
            }
            //todo: stack

            ///IO-space readwrite
            uint8_t& IO(uint8_t c){
                if(c>=0 && c<0x40) //todo: write protection
                    operator[](c+(uint8_t)0x20);
            }

            ///general purpose register read-write
            uint8_t& GP(uint8_t c){
                if(c>=0 && c<0x20)
                    operator[](c);
            }

            ///RAM read write
            uint8_t& SRAM(uint8_t c){
                if(c>=0&&c<0x20)
                    operator[](c+(uint8_t)0x60);
            }

            ///absolute read.write
            uint8_t& operator[] (uint8_t c){
                return data[c];
            }

            ///dump ram contents in humar readable form
            void dump(std::ostream &o);


    };

}
#endif //ATTINY13_EMULATOR_SRAM_H
