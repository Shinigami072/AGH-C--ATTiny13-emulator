//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_SRAM_H
#define ATTINY13_EMULATOR_SRAM_H

#include <array>
#include <functional>
#include "../Utils.h"
#include "RegisterAdapter.h"

namespace emulator {
    class SRAMmemory {
        protected:
            std::array<uint8_t, 32+64+64> data;
            class StackAdapter{
                public:
                    StackAdapter(){}
                    void push_back(uint8_t item){

                    }
            };
        public:
            ///idea: referencje do nazwanych rejestrów
            uint8_t& SPL;
            ///SREG ITHSVNZC
            RegisterFlagAdapter<1> SREG={std::ref(data[0x3f])};

            SRAMmemory():data(),SPL(data[0x3d]){
                std::fill(data.begin(),data.end(),0);
                SPL=0x9f;

            }

            //todo: stack

            ///IO-space readwrite
            inline uint8_t& IO(uint8_t c){
                if(c>=0 && c<0x40) //todo: write protection
                    operator[](c+(uint8_t)0x20);
            }

            ///general purpose register read-write
            inline uint8_t& GP(uint8_t c){
                if(c>=0 && c<0x20)
                    operator[](c);
            }

            ///RAM read write
            inline uint8_t& SRAM(uint8_t c){
                if(c>=0&&c<0x20)
                    operator[](c+(uint8_t)0x60);
            }

            ///absolute read.write
            inline uint8_t& operator[] (uint8_t c){
                return data[c];
            }

            ///dump ram contents in human readable form
            void dump(std::ostream &o);


    };

}
#endif //ATTINY13_EMULATOR_SRAM_H
