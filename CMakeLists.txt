cmake_minimum_required(VERSION 3.11)
project(ATTiny13-emulator)

set(CMAKE_CXX_STANDARD 11)
set(HEADERS src/Constants.h src/Instructions.h src/instruction/NOP.h src/Emulator.cpp src/Emulator.h src/instruction/RJMP.h src/hexfile/HexLoader.cpp src/hexfile/HexLoader.h src/Utils.h src/ATTinyMemory/SRAM.cpp src/ATTinyMemory/SRAM.h src/instruction/INC.h)
add_executable(emulate src/main.cpp ${HEADERS} src/ATTinyMemory/ATtiny13.cpp src/ATTinyMemory/ATtiny13.h src/instruction/Instruction.cpp src/instruction/Instruction.h src/instruction/InstructionSet.cpp src/instruction/InstructionSet.h)