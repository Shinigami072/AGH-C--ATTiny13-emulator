//
// Created by shinigami on 01/06/18.
//

#ifndef ATTINY13_EMULATOR_HEXLOADER_H
#define ATTINY13_EMULATOR_HEXLOADER_H
#include <map>
#include <vector>
#include <array>
#include <iostream>
#include <utility>
#include <algorithm>
#include "../Utils.h"

namespace utils {
    class hex_invalid_checksum: public std::runtime_error{
    public:
        hex_invalid_checksum(const char *s):runtime_error(s){}
    };
    class hex_invalid_type: public std::runtime_error{
    public:
        uint16_t type;
        hex_invalid_type(const char *s,uint16_t t):runtime_error(s),type(t){}
    };
    ///stores hex file
    class Hex {
    public:
        Hex(){}

        template<int N>
        void loadHex8(const std::array<uint8_t, N>& a){
            lines.clear();
            int i=0;
            auto it = a.begin();
            while(it!=a.end()){
                lines[i]=std::vector<uint8_t >(it,it+16);
                it+=16;
                i+=16;
            }
        }

        template<int N>
        void loadHex16(const std::array<uint16_t, N>& a){
            lines.clear();
            int i=0;
            auto it = a.begin();
            while(it!=a.end()){
                lines[i]=std::vector<uint8_t >(16);
                for(uint8_t z=0;z<8;z++){
                    lines[i][2*z+1]=(*it>>8);
                    lines[i][2*z]=(*it&0xFF);
                    it++;
                }
                i+=16;
            }
        }
        /// converts to 16 bit array
        /// un read values default to 0
        /// \tparam N - word count
        /// \param start -optional address start
        /// \return array N length containing N words
        template<int N>
        std::array<uint16_t, N> toArray16(int start=0) const;

        /// converts hex to 8bit array
        /// \tparam N -byte count
        /// \param start  -optional address start
        /// \return array N length containing N bytes
        template<int N>
        std::array<uint8_t, N> toArray8(int start=0) const;

        friend  class HexLoader;
    private:

        std::map<int, std::vector<uint8_t>> lines;
    };

    class HexLine {
    public:

        uint16_t count;
        uint32_t address;
        uint16_t type;
        uint8_t *data;
        uint16_t checksum;

        HexLine(uint16_t ct, uint32_t addr, uint16_t tp) :
                count(ct), address(addr), type(tp), data(new uint8_t[ct]), checksum(0) {

        }

        HexLine(HexLine &&h) noexcept:
                count(h.count), address(h.address), type(h.type), data(nullptr), checksum(h.checksum) {
            data = h.data;
            h.data = nullptr;
        }

        ~HexLine(){
            if(data!= nullptr)
            delete[] data;
        }


        bool valid() const{
            return calculateChecksum() == checksum;
        }

        uint8_t calculateChecksum() const{
            auto check = (uint8_t)(count + (uint8_t) (0xFFu & address) + (uint8_t) (uint8_t(0xFF) & (uint8_t)address >> 16u) + type);
            for (uint8_t i = 0; i < count; i++)
                check += data[i];
            check = (uint8_t) 0xFFu & (~check) + (uint8_t) 1u;

            return check;
        }

        HexLine(uint8_t ct, uint16_t addr, uint8_t tp, uint8_t *dt, uint8_t chcksm) :
                count(ct), address(addr), type(tp), data(dt), checksum(chcksm) {
            if (!valid())
                throw hex_invalid_checksum("Unable to construct hex with invalid checksum");

        }


        uint8_t &operator[](uint8_t i) {
            return data[i];
        }

    };

    class HexLoader {

        ///un complex helper obj


    public:
        static Hex parse(std::istream &in);
        static void save(std::ostream &out,const Hex& h);
        static void saveLine(std::ostream& out,HexLine);
        static HexLine parseLine(std::istream &in);

        static HexLine endLine();

        static HexLine dataLine(std::vector<uint8_t>& vector, uint32_t i);
    };

    template<int N>
    std::array<uint8_t, N> Hex::toArray8(int start) const{
        std::array<uint8_t, N> block;
        std::fill(block.begin(), block.end(), 0);
        for (std::pair<int, std::vector<uint8_t>> p:lines) {
            std::copy(p.second.begin(), p.second.end(), block.begin() + start + p.first);
        }
        return block;
    }

    template<int N>
    std::array<uint16_t, N> Hex::toArray16(int start) const{
        std::array<uint16_t, N> block;
        std::fill(block.begin(), block.end(), 0);
        //uint16_t tmp;
        for(std::pair<int, std::vector<uint8_t>> p:lines){
            uint t=(uint)start+p.first;
            for(auto i=p.second.begin();i!=p.second.end();i+=1)
            {

                block[t / 2] |= (t%2)==0 ?*i:(*i) << 8u;
                t++;
            }
        }

        return block;
    }
}

#endif //ATTINY13_EMULATOR_HEXLOADER_H
