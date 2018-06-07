//
// Created by shinigami on 01/06/18.
//

#include "HexLoader.h"


namespace hex {

    uint8_t readHex_uint8(std::istream &in) {
        uint8_t t=0;
        char c;

        for(int i=0;i<2;i++){
            in>>c;
            c=hex(c);
            t|=c<<((1-i)*4);
        }
        return t;
    }

    uint16_t readHex_uint16(std::istream &in) {
        uint16_t t=0;
        char c;

        for(int i=0;i<4;i++){
            in>>c;
            c=hex(c);
            t|=c<<((3-i)*4);
        }
        return t;
    }


    class Hex HexLoader::parse(std::istream &in) {
        Hex h;
        bool loaded = false;
        int address =0;
        while (!loaded) {
            HexLoader::HexLine l= parseLine(in);
            if(!l.valid())
                throw "Corrupted hex"; //todo: corrupted Hex
            switch(l.type){
                default:
                    throw "unexpected hex type"; //todo: unexpected hex Hex
                //todo: extended addressing modes
                case 0:{
                    h.lines.insert(
                            std::make_pair(address+l.address,std::vector<uint8_t>(l.data,l.data+l.count)
                            ));
                }
                case 1:{
                    loaded=true;
                }
                case 2:{
                    address=(l.data[0]|l.data[1]<<8)<<4;
                }
            }
        }
        return h;
    }
    HexLoader::HexLine HexLoader::parseLine(std::istream &in){
        char b=0;
        while(b!=':') {
            in >> b;
            if (b != '\n' && b!=':' && b!='\r')
                throw "Illegal Hex Begin";//todo: begin exception
        }
        uint8_t count=readHex_uint8(in);
        uint16_t address=readHex_uint16(in);
        uint8_t type=readHex_uint8(in)
                ,checksum=0;



        HexLoader::HexLine l(count,address,type);
        for(uint16_t i =0;i<count;i++)
            l[i]=readHex_uint8(in);
        checksum = readHex_uint8(in);
        l.checksum=checksum;

        return l;
    }

}