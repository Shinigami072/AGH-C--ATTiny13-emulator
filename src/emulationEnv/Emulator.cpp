//
// Created by shinigami on 01/06/18.
//

#include "Emulator.h"
namespace emulator{

    void Emulator::execute(std::ostream* o) {
        auto instr = instructionSet.find(state.programFlash[state.PC]);
        if(instr == instructionSet.end())
            throw unexpected_instruction("Unexpected/Unsupported Instruction",state.programFlash[state.PC]);

        //wykonanie odpowiedniej instrukcji- i przekazanie odpowiedniego stanu + samej instrukcji
        auto instruction =state.PC;
        (*instr)->execute(state,state.programFlash[instruction]);
        //todo: zwracanie iteratora?
        if(o!= nullptr)
            (*instr)->dump(state, state.programFlash[instruction], instruction, *o);
    }


    Emulator::Emulator():state() {
        instructionSet=ATTiny13_InstructionSet();
    }

    void Emulator::dissasemble(std::ostream &o) {
        int i =0;
        while(i<state.programFlash.size()) {
            auto instr = instructionSet.find(state.programFlash[i]);
            if (instr == instructionSet.end())
                throw unexpected_instruction("Unexpected/Unsupported Instruction", state.programFlash[i]);
            (*instr)->dump(state, state.programFlash[i], i, o);
            i+=(*instr)->length();
        }
    }

}