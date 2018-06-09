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
        (*instr)->execute(state,state.programFlash[state.PC]);
        //todo: zwracanie iteratora?
        if(o!= nullptr)
            *o<<(*instr)->getMnem();
    }


    Emulator::Emulator():state() {
        instructionSet=ATTiny13_InstructionSet();
    }

}