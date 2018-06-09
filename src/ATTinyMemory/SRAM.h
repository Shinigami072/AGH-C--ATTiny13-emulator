//
// Created by shinigami on 07/06/18.
//

#ifndef ATTINY13_EMULATOR_SRAM_H
#define ATTINY13_EMULATOR_SRAM_H

#include <array>
#include <functional>
#include <vector>
#include "../Utils.h"

namespace emulator {


    template <int N=1>
    class RegisterFlagAdapter {
        class register_out_of_range: public std::out_of_range{
        public:
            register_out_of_range(std::string s="stack out of bits"):out_of_range(s){}
        };
    public:
        RegisterFlagAdapter(std::initializer_list<std::reference_wrapper<uint8_t>> l):registers(l){
            if(l.size()!=N)
                throw std::invalid_argument("Register size does not correspond to references");
        }
        /// Set i bool in adapted Register
        /// \param b value to set
        /// \param i location to set
        void setBool(bool b,int i=0){
            if(i<0||i>=N*8)
                register_out_of_range("Error acessing bit"+i);

            if(b)
                registers[i/8]|=1<<(i%8);
            else
                registers[i/8]&=~(1<<(i%8));

        }
        /// get i bool in adapted Register
        /// \param i location to get
        bool getBool(int i=0) const{
            if(i<0||i>=N*8)
                register_out_of_range("Error acessing bit"+i);

            return (registers[i/8]&(1u<<(i%8)))!=0;

        }

        uint8_t& getByte(int i=0){
            if(i<0||i>=N)
                register_out_of_range("Error acessing byte"+i);
            return registers[i];
        }

        void setByte(uint8_t b,int i=0){
            if(i<0||i>=N)
                register_out_of_range("Error acessing byte"+i);
            registers[i]=b;
        }

    private:
        std::vector<std::reference_wrapper<uint8_t>> registers;
    };


    class SRAMmemory {
        protected:
            std::array<uint8_t, 32+64+64> data;
            class StackAdapter{
                class stack_out_of_range: public std::out_of_range{
                public:
                    stack_out_of_range(std::string s="stack out of memory"):out_of_range(s){}
                };

                public:
                    StackAdapter(uint8_t& _SPL, std::array<uint8_t, 32+64+64>& _data):data(_data),SPL(_SPL){}
                    void push_back(uint8_t item){
                        if(SPL-1<95)
                            throw stack_out_of_range();
                        data[SPL--]=item;

                    }
                    void push_back(uint16_t item){
                        if(SPL-2<95)
                            throw stack_out_of_range();
                         data[SPL--]=item;
                         data[SPL--]=item>>8u;

                    }
                    uint8_t pop_back(){
                        if(SPL+1>data.size())
                            throw stack_out_of_range("pop on empty stack");
                        return data[++SPL];
                    }
                    uint16_t pop_back16(){
                        if(SPL+2>data.size())
                            throw stack_out_of_range("pop on empty stack");
                        uint16_t t =(data[++SPL]<<8u)|(data[++SPL]);
                        return t;
                    }

            private:
                    std::array<uint8_t, 32+64+64>& data;
                    uint8_t& SPL;
            };

        public:
            ///idea: referencje do nazwanych rejestrów
            uint8_t& SPL;
            ///SREG ITHSVNZC
            RegisterFlagAdapter<1> SREG={std::ref(data[0x3f])};
            StackAdapter stack;
            SRAMmemory():data(),SPL(data[0x3d]),stack(SPL,data){
                std::fill(data.begin(),data.end(),0);
                SPL=0x9f;

            }

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
            void dump(std::ostream &o) const;


    };

}
#endif //ATTINY13_EMULATOR_SRAM_H
