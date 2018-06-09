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
        Instruction(const char* mask,const std::string& mnemonic);
        virtual ~Instruction() = default;

        ///virtualana fukcja - wykonuje daną instrukcje na podanym attiny
        virtual void execute(class ATtiny13& at,uint16_t instruction) const = 0;

        ///porównanie - sprawdzenie czy wczytana instrucja jest dana istrukcją
        bool operator == (uint16_t instruction) const{
            return (instruction&instrMask)==instrVal;
        }

        ///porównanie szeregujące 2 instrukcje
        bool operator < (const Instruction& b) const{
            return instrVal<b.instrVal;
        }

        ///porównanie szeregujące wyszukiwaną instrujczę z obecną instrukjcą
        bool operator < (uint16_t instruction) const{
            return (instruction&instrMask)<instrVal;
        }

    public://todo - protected
        uint16_t instrMask;
        uint16_t instrVal;
        uint16_t kMask,KMask;

        std::string mnem;//todo: getter for mnemonic

    };

    ///rozszeżenie podstawowej instrukcji - instrukcja z 1 operatorem(rejestrem Rd)
    class OneOperand: public Instruction {
    public:
        OneOperand(const char* mask,const std::string& mnemonic): Instruction(mask,mnemonic),RdMask(0){
            for(size_t i=0;i<16;i++)
                switch(mask[i]) {
                    case 'd':
                        RdMask |= 1u << 15-i;
                        break;
                    default:;
                }
        }
    protected:
        uint16_t RdMask;
    };

    ///rozszeżenie podstawowej instrukcji - instrukcja z 2 operatorem(rejestrem Rd, rejestrem Rr)
    class TwoOperand: public Instruction {
    public:
        TwoOperand(const char* mask,const std::string& mnemonic): Instruction(mask,mnemonic),RdMask(0),RrMask(0){
            for(size_t i=0;i<16;i++)
                switch(mask[i]) {
                    case 'd':
                        RdMask |= 1u << 15-i;
                        break;
                    case 'r':
                        RrMask |= 1u << 15-i;
                        break;
                    default:;
                }
        }
    protected:
        uint16_t RdMask;
        uint16_t RrMask;
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTION_H
