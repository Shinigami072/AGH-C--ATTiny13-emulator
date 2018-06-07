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

namespace hex {

    class Hex {
    public:
        template<int N>
        std::array<uint16_t, N> toArray16(int start=0);

        template<int N>
        std::array<uint8_t, N> toArray8(int start=0);

        friend  class HexLoader;
    private:
        std::map<int, std::vector<uint8_t>> lines;
    };

    class HexLoader {
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

            HexLine(HexLine &&h) :
                    count(h.count), address(h.address), type(h.type), data(nullptr), checksum(h.checksum) {
                data = h.data;
                h.data = nullptr;
            }


            bool valid() {
                return calculateChecksum() == checksum;
            }

            uint8_t calculateChecksum() {
                uint8_t check = count + (uint8_t) (0xFF & address) + (uint8_t) (0xFF & address >> 16) + type;
                for (uint8_t i = 0; i < count; i++)
                    check += data[i];
                check = (uint8_t) 0xFF & (~check) + (uint8_t) 1;

                return check;
            }

            HexLine(uint8_t ct, uint16_t addr, uint8_t tp, uint8_t *dt, uint8_t chcksm) :
                    count(ct), address(addr), type(tp), data(dt), checksum(chcksm) {
                if (!valid())
                    throw "WrongChecksum"; //todo: checksum Exception

            }

            ~HexLine() {
                delete[] data;
            }

            uint8_t &operator[](uint8_t i) {
                return data[i];
            }

        };

    public:
        static Hex parse(std::istream &in);

        static HexLine parseLine(std::istream &in);

    };
    template<int N>
    std::array<uint8_t, N> Hex::toArray8(int start) {
        std::array<uint8_t, N> block;
        std::fill(block.begin(), block.end(), 0);
        for (std::pair<int, std::vector<uint8_t>> p:lines) {
            std::copy(p.second.begin(), p.second.end(), block.begin() + start + p.first);
        }
        return block;
    }

    template<int N>
    std::array<uint16_t, N> Hex::toArray16(int start) {
        std::array<uint16_t, N> block;
        std::fill(block.begin(), block.end(), 0);
        //uint16_t tmp;
        for(std::pair<int, std::vector<uint8_t>> p:lines){
            int t=p.first;
            for(auto i=p.second.begin();i!=p.second.end();i+=1)
            {

                block[t / 2] |= (t%2)==0 ?*i:(*i) << 8;
                t++;
            }
        }

        return block;
    }
}

#endif //ATTINY13_EMULATOR_HEXLOADER_H
