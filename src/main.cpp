#include <iostream>
#include "ATTinyMemory/ATtiny13.h"
#include "emulationEnv/Emulator.h"
#include "hexfile/HexLoader.h"
#include "fstream"
#include <chrono> // std::chrono::microseconds
#include <thread> // std::this_thread::sleep_for;
#include <iomanip>
#include <stdexcept>

class options: public std::invalid_argument {
public:
    options(char* s):invalid_argument(s){}
};

using namespace emulator;
using namespace utils;

enum state{
    DEFAULT,
    LIST,
    HELP,
    VERSION,
    EMULATE,
    DISPLAY
};
struct Option{
    std::string pathSRAM;
    std::string pathProgram;
    std::string commandsList;
    std::string output;
    bool save;
    bool program;
    bool sram;
    bool out;
    state state1;
    int t;
    uint16_t counter;
    bool limit;
    bool dissasemble;
    bool mute;
};

int flags_long(Option& o,int j,int argc,char** argv){

}

int flags_short(Option& o,int j,int argc,char** argv){
    switch(argv[j][1]){
        case 't':
            if(o.limit)
                throw options("repeated step flag");
            o.limit=true;
            o.t=std::stoi(argv[j+1]);
            return j+1;
        case 'h':
            if(o.state1 != DEFAULT)
                throw options("repeated list flag");
            o.state1=HELP;
            return j;
        case 'v':
            if(o.state1 != DEFAULT)
                throw options("repeated version flag");
            o.state1=VERSION;
            return j;
        case 'l':
            if(o.state1 != DEFAULT)
                throw options("repeated list flag");
            o.state1=LIST;
//            if(argv[j+1][0]!='-')
//            {
//                o.commandsList="LIST.lst";
//                return j+2;
//            }//todo:: ability to savelist to file
        return j;
        case 'c':
            o.counter=uint16_t (std::stoi(argv[j+1]));
            return j+1;
        case 'o':
            if(o.out)
                throw options("repeated output flag");
            o.out=true;
            o.output=argv[j+1];
            return j+1;
        case 'd':
            if(o.dissasemble || (o.state1!=DEFAULT&&o.state1!=EMULATE) )
                throw options("repeated disassemble");
            o.dissasemble=true;
            o.state1=EMULATE;
            return j;
        case 'm':
            if(o.mute || (o.state1!=DEFAULT&&o.state1!=EMULATE) )
                throw options("repeated mute");
            o.mute=true;
            o.state1=EMULATE;
            return j;
        case 'i':
            if(!o.program) 
                throw options("wrong display");
            o.state1=DISPLAY;
        return j;
        case 'p':
            if(o.program || (o.state1!=DEFAULT&&o.state1!=EMULATE) )
                throw options("repeated program");
            o.program=true;
            o.state1=EMULATE;
            o.pathProgram=argv[j+1];
        return j+1;
        case 's':
            if(o.sram || (o.state1!=DEFAULT&&o.state1!=EMULATE) )
                throw options("repeated sram");
            o.sram=true;
            o.state1=EMULATE;
            o.pathSRAM=argv[j+1];
            return j+1;
        default:
            throw options("unrecognised option");
    }
}
//todo: dissasembler
//todo: allow step-by step execution
//todo: allow timed execution
Option handleoptions(int argc,char** argv){
    Option o={"SRAM.hex","Program.hex","todo:implement::","out_",false,false,false,false,DEFAULT,0,0,false,false,false};
    int i =0;
    for(int j=0;j<argc;j++){
        switch(argv[j][0]){
            case '-':
                if(argv[j][1]=='-')
                    j=flags_long(o,j,argc,argv);
                else
                    j=flags_short(o,j,argc,argv);
                continue;
            default: break;
        }

    }
    if((!o.program)&&(o.state1==DEFAULT || o.state1==EMULATE || o.state1==DISPLAY))
        throw options("Program File not found");
    return o;
};

void help() {
    //todo:: usage
    std::cout<<"Usage:"<<std::endl;
    std::cout<<"\temulate -h"<<std::endl;
    std::cout<<"\temulate -l"<<std::endl;
    std::cout<<"\temulate -v"<<std::endl;
    std::cout<<"\temulate [-d] -p <path> -s <path> [-t <num>] [-c <num>] [-o <pathBegin>]"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"options:"<<std::endl;
    std::cout<<"\t-h - display this information"<<std::endl;
    std::cout<<"\t-l - display implemented instructions"<<std::endl;
    std::cout<<"\t-v - display this version information"<<std::endl;
    std::cout<<std::endl;
    std::cout<<"program emulation options:"<<std::endl;
    std::cout<<"\t-i - just display selected state from program file"<<std::endl;
    std::cout<<"\t-d - dissasemble this selected program file"<<std::endl;
    std::cout<<"\t-m - mute execuion"<<std::endl;
    std::cout<<"\t-t <num> - set step limit to <num>"<<std::endl;
    std::cout<<"\t-c <num> - set PC to <num>"<<std::endl;
    std::cout<<"\t-o <pathBegin> - set output path beggining"<<std::endl;
    std::cout<<"\t-p <path> - point to program hex"<<std::endl;
    std::cout<<"\t-s <path> - point to sram hex"<<std::endl;

}

void version() {
    std::cout<<"Version: "<<VERSION_NUMBER<<std::endl;
}

void list(std::ostream& o) {
    o<<"Instructions:"<<std::endl;
    ATTiny13_InstructionSet i;
    i.printInstructionList(o);
}

void emulate(Option &option) {
    Emulator tiny;
    {
        std::ifstream program(option.pathProgram);
        tiny.state.flash(HexLoader::parse(program).toArray16<512>());
        program.close();
    }

    if(option.sram)
    {
        std::ifstream sram(option.pathProgram);
        tiny.state.memory.flash(HexLoader::parse(sram).toArray8<160>());
        sram.close();
    }
    tiny.state.PC=option.counter;

    if(option.dissasemble){
        std::cout<<"Disassembly:"<<std::endl;
        tiny.dissasemble(std::cout);
    }

    size_t i=0;
    if(option.state1 == DISPLAY){
        tiny.state.dump(std::cout);
        return;
    }

    while(   (i < option.t || !option.limit) &&
             tiny.state.PC < tiny.state.programFlash.size() ) {

        tiny.execute(option.mute? nullptr:&std::cout);
        i++;
    }

    tiny.state.dump(std::cout);
    if(option.out){
        std::ofstream out_human(option.output+"state.human",std::ofstream::trunc);
        tiny.state.dump(out_human);
        out_human.close();

        std::ofstream hexerprogram(option.output+"FLASH.hex",std::ofstream::trunc);
        std::ofstream hexersram(option.output+"SRAM.hex",std::ofstream::trunc);

        Hex hex_temp;
        hex_temp.loadHex16<512>(tiny.state.programFlash);
        HexLoader::save(hexerprogram,hex_temp);

        hex_temp.loadHex8<160>(tiny.state.memory.getData());
        HexLoader::save(hexersram,hex_temp);
    }
}

int main(int argc, char** argv) {
    try {
        Option o = handleoptions(argc, argv);
        switch(o.state1){
            default:
            case DEFAULT:
            case EMULATE:
            case DISPLAY:
                std::cout<<"starting..."<<std::endl;
                emulate(o);
                return 0;

            case HELP:
                help();
                return 0;
            case VERSION:
                version();
                return 0;
            case LIST:
                list(std::cout);
                return 0;
        }
    }catch(options& o){
        std::cerr<<o.what()<<std::endl;
        std::cout<<"Unexpected Usage, use -h for help"<<std::endl;
        return -1;
    }


    return -1;
}
