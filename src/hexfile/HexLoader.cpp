//
// Created by shinigami on 01/06/18.
//

#include "HexLoader.h"


namespace utils {

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

    HexLine addressLine(uint16_t addr){
        HexLine h(2,0,2);
        h.data[0]=uint8_t (addr);
        h.data[1]=uint8_t (addr>>8);
        h.checksum=h.calculateChecksum();
        return h;
    }

    HexLine HexLoader::endLine() {
        HexLine h(0, 0, 1);
        h.checksum=h.calculateChecksum();
        return h;
    }

    ///parsehex file into hex object
    class Hex HexLoader::parse(std::istream &in){
        Hex h;
        bool loaded = false;
        uint address =0;
        while (!loaded) {
                HexLine l= parseLine(in);
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
    HexLine HexLoader::parseLine(std::istream &in){
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



        HexLine l(count,address,type);

        //read in bytes
        for(uint16_t i =0;i<count;i++)
            l[i]=readHex_uint8(in);

        checksum = readHex_uint8(in);//read checksum
        l.checksum=checksum;//save shecksum

        return l;
    }


    void HexLoader::save(std::ostream &out, const Hex &h) {
        bool addUpd =false;
        uint16_t addr = 0;
        for(auto p:h.lines)
        {
            if(p.first-addr>=(1<<17))
                addUpd=false;
            if(!addUpd){
                addr=static_cast<uint16_t>(p.first);
                addUpd=true;
                saveLine(out,addressLine(addr));
            }

            //save data
            saveLine(out,dataLine(p.second,uint32_t (p.first-addr)));

        }
        saveLine(out,endLine());
    }

    HexLine HexLoader::dataLine(std::vector<uint8_t>& vector,uint32_t i) {
        HexLine h(uint16_t(vector.size()), i, 0);
        int b=0;
        for(uint8_t d:vector){
            h.data[b++]=d;
        }
        h.checksum=h.calculateChecksum();
        return h;
    }

    char toHex_Char(uint8_t u){
        if(u<10)
            return '0'+u;
        else
            return 'A'+(u-10);
    }
    std::string toHex8(uint8_t u){
        std::string s="XX";
        s[0]=toHex_Char((u>>4)&0xF);
        s[1]=toHex_Char(u&0xF);

        return s;
    }

    std::string toHex16(uint16_t u){
        std::string s="XXXX";
        s[0]=toHex_Char((u>>12)&0xF);
        s[1]=toHex_Char((u>>8)&0xF);
        s[2]=toHex_Char((u>>4)&0xF);
        s[3]=toHex_Char(u&0xF);

        return s;
    }

    void HexLoader::saveLine(std::ostream &out, HexLine h) {
        out<<":"<<toHex8(h.count)<<toHex16(h.address)  <<toHex8(h.type);
        uint8_t u=h.count;
        while(u>0){
            out<<toHex8(h.data[h.count-u]);
            u--;
        }
        out<<toHex8(h.checksum)<<std::endl;
    }


//todo: savestuff cleanup

}