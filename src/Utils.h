//
// Created by shinigami on 04/06/18.
//

#ifndef ATTINY13_EMULATOR_UTILS_H
#define ATTINY13_EMULATOR_UTILS_H
#include <bitset>
#include <string>
#include <cstring>
#include <sstream>

namespace hex{
    char inline hex(char h){
        switch(h)
        {
            default:
                throw -3;//todo: unexpected char
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'a':
            case 'A':
                return 10;
            case 'b':
            case 'B':
                return 11;
            case 'c':
            case 'C':
                return 12;
            case 'd':
            case 'D':
                return 13;
            case 'e':
            case 'E':
                return 14;
            case 'f':
            case 'F':
                return 15;
        }
    }
    inline const std::string bin8(uint8_t val) {
        std::stringstream c;
        c<<std::bitset<8>(val);
        return c.str();
    }

    inline const std::string bin16(uint16_t val){
        std::stringstream c;
        c<<std::bitset<16>(val);
        return c.str();

    }

    template<char N>
    inline const int16_t U2(uint16_t val){
        int16_t out=0;
        for(char i=0;i<N;i++){
            if((val&(1<<i))!=0)
                if(i==N-1)
                    out-=1<<i;
                else
                    out+=1<<i;
        }
        return out;
    }
}
#endif //ATTINY13_EMULATOR_UTILS_H
