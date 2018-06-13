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


    class RegisterFlagAdapter {
        class register_out_of_range: public std::out_of_range{
        public:
            register_out_of_range(std::string s="stack out of bits"):out_of_range(s){}
        };
    public:
        RegisterFlagAdapter(uint8_t& l):_register(l){}
        /// Set i bool in adapted Register
        /// \param b value to set
        /// \param i location to set
        void setBool(bool b,int i=0);
        /// get i bool in adapted Register
        /// \param i location to get
        bool getBool(int i=0) const;

        uint8_t& getByte(){
            return _register;
        }

        inline void setByte(uint8_t b){
            _register=b;
        }

    private:
        uint8_t& _register;
    };

    class RegisterWordAdapter {

    public:
        RegisterWordAdapter(uint8_t& l,uint8_t& h):_register_low(l),_register_high(h){}

        explicit operator uint16_t (){
            return ((_register_high)<<8u)|_register_low;
        }

        ///preincrement
        uint16_t operator ++(){
            if(_register_low==0xff)
                _register_high++;
            _register_low++;
            return operator uint16_t ();
        }

        ///postincrement
        uint16_t operator ++(int){
            uint16_t t =uint16_t();
            operator++();

            return t;
        }

        ///predecrement
        uint16_t operator --(){
            if(_register_low==0x00)
                _register_high--;
            _register_low--;
            return operator uint16_t ();
        }

        ///postdecrement
        uint16_t operator --(int){
            uint16_t t =operator uint16_t();
            operator++();

            return t;
        }


        ///addition
        uint16_t operator +(uint16_t a){
            uint16_t t =operator uint16_t();
            return t+a;
        }

        ///=addition
        uint16_t operator +=(uint16_t a){
            if(_register_low>=0xff-a&0xFF)
                _register_high++;
            _register_low+=a&0xFF;
            _register_high+=(a>>8u)&0xFF;

            return operator uint16_t();
        }

        ///subtraction
        uint16_t operator -(uint16_t a){
            uint16_t t =operator uint16_t();
            return t-a;
        }

        ///=subtraction
        uint16_t operator -=(uint16_t a){
            if(_register_low<=a&0xFF)
                _register_high--;
            _register_low-=a&0xFF;
            _register_high-=(a>>8u)&0xFF;

            return operator uint16_t();
        }


        uint8_t& getByte(bool low=true){
            return low?_register_low:_register_high;
        }

        inline void setByte(uint8_t b,bool low=true){
            if(low)
                _register_low=b;
            else
                _register_high=b;

        }

    private:
        uint8_t& _register_low;
        uint8_t& _register_high;

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
                        if(SPL-1<0x60)
                            throw stack_out_of_range();
                        data[SPL--]=item;

                    }
                    void push_back(uint16_t item){
                        if(SPL-2<0x60)
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
            //todo - X,Y,Z Register adapters

            ///idea: referencje do nazwanych rejestrów
            uint8_t& SPL;
            ///SREG ITHSVNZC
            RegisterFlagAdapter SREG;
            RegisterWordAdapter X,Y,Z;
            StackAdapter stack;
            SRAMmemory():
                        data(),
                        SPL(data[0x3d]),
                        SREG(data[0x3f]),
                        stack(SPL,data),
                        X(data[0x1A],data[0x1B]),
                        Y(data[0x1C],data[0x1D]),
                        Z(data[0x1E],data[0x1F]){
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
