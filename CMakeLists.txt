cmake_minimum_required(VERSION 3.11)
project(ATTiny13-emulator)

set(CMAKE_CXX_STANDARD 11)
set(HEADERS src/Constants.h src/instruction/ALU/ADD.h src/instruction/Instructions.h src/instruction/ALU/DEC.h src/instruction/ALU/SER.h  src/instruction/ALU/CLR.h src/instruction/NOP.h src/emulationEnv/Emulator.cpp src/emulationEnv/Emulator.h src/instruction/RJMP.h src/hexfile/HexLoader.cpp src/hexfile/HexLoader.h src/Utils.h src/ATTinyMemory/SRAM.cpp src/ATTinyMemory/SRAM.h src/instruction/ALU/INC.h src/ATTinyMemory/RegisterAdapter.cpp src/ATTinyMemory/RegisterAdapter.h src/instruction/ALU/SER.h)
add_executable(emulate src/main.cpp ${HEADERS} src/ATTinyMemory/ATtiny13.cpp src/ATTinyMemory/ATtiny13.h src/instruction/Instruction.cpp src/instruction/Instruction.h src/emulationEnv/InstructionSet.cpp src/emulationEnv/InstructionSet.h)