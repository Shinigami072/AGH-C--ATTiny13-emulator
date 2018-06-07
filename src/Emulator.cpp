//
// Created by shinigami on 01/06/18.
//

#include "Emulator.h"
namespace emulator{
    void Emulator::execute() {
        auto instr = instructionSet.find(state.programFlash[state.PC]);
        // auto instr = find(instructionSet.begin(),instructionSet.end(),state.programFlash[state.PC]);
        if(instr == instructionSet.end())
            throw -1;//todo: Unsupported Instruction programFlash[PC]
        (*instr)->execute(state,state.programFlash[state.PC]);
    }

    Emulator::Emulator() {
        instructionSet=ATTiny13_InstructionSet();
    }

}