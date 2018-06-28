//
// Created by shinigami on 04/06/18.
//

#ifndef ATTINY13_EMULATOR_UTILS_H
#define ATTINY13_EMULATOR_UTILS_H

#include <bitset>
#include <string>
#include <sstream>


///Funkcje pomocnicze
namespace utils{
    /// testIf Bit set
    /// \tparam N bit to test
    /// \param t byte to test
    /// \return is N bit Set
    template<int N>
    bool inline isSet(uint16_t t){
        if(N>16||N<=0)
            throw std::overflow_error("Unable to represent "+std::to_string(N)+"bits in 16 bits");
        return (t&1u<<N)!=0;
    }

    /// clear N Bit
    /// \tparam N bit to clear
    /// \param t byte to clear
    /// \return cleared byte
    template<int N>
    uint16_t inline clrSet(uint16_t t){
        if(N>16||N<=0)
            throw std::overflow_error("Unable to represent "+std::to_string(N)+"bits in 16 bits");
        return (t&(uint16_t)(~(1u<<N)));
    }


    std::string inline getRG_str(uint8_t i){
        return "r"+std::to_string((short)i);
    }
    char inline getSRAM_FLAG(uint8_t i){
        return "CZNVSHTI"[i];
    }


    /// hex - zamienia char na odpowiadającą mu liczbę
    /// \param h char z Kodem hex
    /// \return odpowiednik danego chara, jako liczba
    uint8_t inline hex(char h){
        switch(h)
        {
            default:
                throw std::invalid_argument(std::string("Invalid hex_char(")+h+"]");
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


    /// bin8 - zamiania 8bit wartość na sting zawierający 10
    /// \see bin16 - warsja 16 bit
    /// \param val pobierana wartość
    /// \return string -bedący repezntacją binarną podanej wartości
    inline const std::string bin8(uint8_t val) {
        std::stringstream c;
        c<<std::bitset<8>(val);
        return c.str();
    }

    /// bin16 - zamiana 16bit wartość na string zawierąjcy 10
    /// \see bin8 wersja 8bit
    /// \param val pobierana wartość
    /// \return string - reprezenatacja binarna 16 bitowej wartości
    inline const std::string bin16(uint16_t val){
        std::stringstream c;
        c<<std::bitset<16>(val);
        return c.str();

    }

    /// U2<N> zamiana Nbit wartości (0<N<=16) za pomocą systemu U2
    /// \tparam N ilość bitów
    /// \param val reprezentowana wartość
    /// \return wartość ze znakiem
    template<uint8_t N>
    inline const int16_t U2(uint16_t val){
        if(N>16||N<=0)
            throw std::overflow_error("Unable to represent "+std::to_string(N)+"bits in 16 bits");

        int16_t out=0;
        //U2 zamina od najwyższego bitu
        if((val&(1u<<(N-1)))!=0)
            out+=-1;
        //konstrukcja zpozostałych bitów
        for(int8_t i=N-2;i>=0;i--){
            out*=2;
            if((val&(1u<<(i)))!=0)
                out+=1;

        }
        return out;
    }
}
#endif //ATTINY13_EMULATOR_UTILS_H
