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
        Instruction(const char* mask,const std::string& group,const std::string& mnemonic);
        virtual ~Instruction() = default;

        ///virtualana fukcja - wykonuje daną instrukcje na podanym attiny
        virtual void execute(class ATtiny13& at,uint16_t instruction) const = 0;

        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) {
            out<<getMnem()<<std::endl;
        }
        virtual uint8_t length(){
            return 1;
        }

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

        const std::string& getMnem() const{
            return mnem;
        }

        const uint16_t getInstrMask() const{
            return instrMask;
        }

        const uint16_t getInstrVal() const{
            return instrVal;
        }

    protected:
        uint16_t instrMask;
        uint16_t instrVal;
        uint16_t kMask,KMask;

        std::string mnem;
        std::string grp;
    };

    ///rozszeżenie podstawowej instrukcji - instrukcja z 1 operatorem(rejestrem Rd)
    class OneOperand: public Instruction {
    public:
        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            out<<getMnem()<<" "<<utils::getRG_str(RdVal)<<std::endl;
        }
        uint8_t getRegisterRD(uint16_t instruction) const{
            auto RdVal = uint8_t (uint(instruction&RdMask)>>4u);
            return RdVal;
        }
        OneOperand(const char* mask,const std::string& group,const std::string& mnemonic): Instruction(mask,group,mnemonic),RdMask(0){
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
        virtual void dump(const ATtiny13 &at, uint16_t instruction, int PC, std::ostream &out) override{
            auto RdVal = getRegisterRD(instruction);
            auto RrVal = getRegisterRR(instruction);
            out<<getMnem()<<" "<<utils::getRG_str(RdVal)<<","<<utils::getRG_str(RrVal)<<std::endl;
        }
        TwoOperand(const char* mask,const std::string& group,const std::string& mnemonic): Instruction(mask,group,mnemonic),RdMask(0),RrMask(0){
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
        uint8_t getRegisterRD(uint16_t instruction) const{
            auto RdVal = static_cast<uint8_t>(uint(instruction&RdMask)>>4u);
            return RdVal;
        }
        uint8_t getRegisterRR(uint16_t instruction) const{
            auto RrVal = utils::isSet<9>(instruction&RrMask)?static_cast<uint8_t>(((instruction&RrMask)^(1u<<10))|(1u<<4)):static_cast<uint8_t>(instruction&RrMask);
            return RrVal;
        }
        uint16_t RdMask;
        uint16_t RrMask;
    };
}

#endif //ATTINY13_EMULATOR_INSTRUCTION_H
