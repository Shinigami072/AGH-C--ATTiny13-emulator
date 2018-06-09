//
// Created by shinigami on 01/06/18.
//

#include "HexLoader.h"


namespace utils {
    //todo: hexfile saveable


    uint8_t readHex_uint8(std::istream &in) {
        uint8_t t=0;
        uint8_t c;

        for(uint i=0;i<2;i++){
            in>>c;
            c=hex(c);
            t|=c<<((1-i)*4);
        }
        return t;
    }

    uint16_t readHex_uint16(std::istream &in) {
        uint16_t t=0;
        uint8_t c;

        for(uint i=0;i<4;i++){
            in>>c;
            c=hex(c);
            t|=c<<((3-i)*4);
        }
        return t;
    }

    ///parsehex file into hex object
    class Hex HexLoader::parse(std::istream &in) const{
        Hex h;
        bool loaded = false;
        uint address =0;
        while (!loaded) {
            HexLoader::HexLine l= parseLine(in);
            if(!l.valid())
                throw hex_invalid_checksum("Invalid checksum - possibly corrupted file");
            switch(l.type){
                default:
                    throw hex_invalid_type("unexpected hex type",l.type);
                //todo: extended addressing modes
                //data type
                case 0:{
                    h.lines.insert(
                            std::make_pair(address+l.address,std::vector<uint8_t>(l.data,l.data+l.count)
                            ));
                }
                break;
                //loaded type
                case 1:{
                    loaded=true;
                }
                break;
                //addres type
                case 2:{
                    address=uint(l.data[0]|l.data[1]<<8u)<<4u;
                }
                break;
            }
        }
        return h;
    }
    HexLoader::HexLine HexLoader::parseLine(std::istream &in)const{
        char b=0;
        while(b!=':') {
            in >> b;
            if (b != '\n' && b!=':' && b!='\r')
                throw std::domain_error("Illegal Hex Begin");
        }
        uint8_t count=readHex_uint8(in); //read byte count
        uint16_t address=readHex_uint16(in); //read 16bit address
        uint8_t type=readHex_uint8(in) //read linetype
                ,checksum=0;



        HexLoader::HexLine l(count,address,type);

        //read in bytes
        for(uint16_t i =0;i<count;i++)
            l[i]=readHex_uint8(in);

        checksum = readHex_uint8(in);//read checksum
        l.checksum=checksum;//save shecksum

        return l;
    }

}