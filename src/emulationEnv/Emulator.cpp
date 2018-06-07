//
// Created by shinigami on 01/06/18.
//

#include "Emulator.h"
namespace emulator{

    void Emulator::execute() {
        auto instr = instructionSet.find(state.programFlash[state.PC]);
        if(instr == instructionSet.end())
            throw -1;//todo: Unsupported Instruction programFlash[PC]
        //wykonanie odpowiedniej instrukcji- i przekazanie odpowiedniego stanu + samej instrukcji
        (*instr)->execute(state,state.programFlash[state.PC]);
    }


    Emulator::Emulator():state() {
        instructionSet=ATTiny13_InstructionSet();
    }

}