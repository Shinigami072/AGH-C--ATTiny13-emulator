//
// Created by shinigami on 08/06/18.
//

#ifndef ATTINY13_EMULATOR_REGISTERADAPTER_H
#define ATTINY13_EMULATOR_REGISTERADAPTER_H

#include <array>
#include <vector>
#include <functional>
#include "../Utils.h"
namespace emulator {

    template <int N=1>
    class RegisterFlagAdapter {
    public:
        RegisterFlagAdapter(std::initializer_list<std::reference_wrapper<uint8_t>> l):registers(l){
            if(l.size()!=N)
                throw -20;//todo: wrong initialization exception
        }

        void setBool(bool b,int i=0){
            if(b)
                registers[i/8]|=1<<(i%8);
            else
                registers[i/8]&=~(1<<(i%8));

        }
        bool getBool(int i=0){
            return (registers[i/8]&(1u<<(i%8)))!=0;

        }

        uint8_t& getByte(int i=0){
            if(i<0||i>=N)
                throw -1;//todo: outofBounds Exception
            return registers[i];
        }
        void setByte(uint8_t b,int i=0){
            if(i<0||i>=N)
                throw -1;//todo: outofBounds Exception
            registers[i]=b;
        }
    private:
        std::vector<std::reference_wrapper<uint8_t>> registers;
    };

}
#endif //ATTINY13_EMULATOR_REGISTERADAPTER_H
