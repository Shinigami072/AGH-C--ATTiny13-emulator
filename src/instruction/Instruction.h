//
// Created by shinigami on 31/05/18.
//

#ifndef ATTINY13_EMULATOR_INSTRUCTION_H
#define ATTINY13_EMULATOR_INSTRUCTION_H

#include <cstring>
#include "../ATTinyMemory/ATtiny13.h"
#include "../Utils.h"
namespace emulator{
    class Instruction {
    public:
        Instruction(const char* mask,std::string mnemonic):instrMask(0),kMask(0),instrVal(0),mnem(mnemonic){
            if(strlen(mask)!=16)
                throw -2;//todo: wrong mask instrMaskargument exception
            for(size_t i=0;i<16;i++)
                switch(mask[i]) {
                    case '1':
                        instrMask |= 1 << 15-i;
                        instrVal |=1 << 15-i;
                    break;
                    case '0':
                        instrMask |= 1 << 15-i;
                    break;
                    case 'k':
                        kMask |= 1 << 15-i;
                    break;
                    default:;
                }
        }
        virtual ~Instruction() = default;

        virtual void execute(class ATtiny13& at,uint16_t instruction) const = 0;

        bool operator == (uint16_t instruction) const{
            return (instruction&instrMask)==instrVal;
        }
        bool operator < (const Instruction& b) const{
            return instrVal<b.instrVal;
        }
        bool operator < (uint16_t instruction) const{
            return (instruction&instrMask)<instrVal;
        }
    public://todo - protected
        uint16_t instrMask;
        uint16_t instrVal;
        uint16_t kMask;
        std::string mnem;

    };

    class OneOperand: public Instruction {
        OneOperand(const char* mask,std::string mnemonic): Instruction(mask,mnemonic),RdMask(0){
            for(size_t i=0;i<16;i++)
                switch(mask[i]) {
                    case 'd':
                        RdMask |= 1 << 15-i;
                        break;
                    default:;
                }
        }
    protected:
        uint16_t RdMask;
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTION_H
