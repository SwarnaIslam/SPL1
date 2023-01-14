#ifndef PSEUDO_H
#define PSEUDO_H
#include<vector>
#include<map>
#include"format.h"
#include"definition.h"
#include"Algorithm.h"
using namespace std;
enum Instructions{
    ABS=1, LI=2, MOVE=3, ORI=4, SGT=5,BLT=6, BGT=7
};
map<string, Instructions>strToEnum;
void initialize(){
    strToEnum["move"]=MOVE;
    strToEnum["li"]=LI;
    strToEnum["abs"]=ABS;
    strToEnum["ori"]=ORI;
    strToEnum["sgt"]=SGT;
    strToEnum["blt"]=BLT;
    strToEnum["bgt"]=BGT;
}
void absExtension(vector<string>command){
    def::mapPseudo[def::trimLen].first=command;
    def::mapPseudo[def::trimLen].second=3;
    def::trimmedInstruction[def::trimLen++]=vector<string>{"sra","$at",command[2],"31"};
    def::trimmedInstruction[def::trimLen++]=vector<string>{"xor",command[1], command[2],"$at"};
    def::trimmedInstruction[def::trimLen++]=vector<string>{"subu",command[1],command[1],"$at"};
}

void liExtension(vector<string>command){
    int number=stoi(command[2]);
    if(number<=32767 && number>=-32768){
        def::mapPseudo[def::trimLen].first=command;
        def::mapPseudo[def::trimLen].second=1;

        def::trimmedInstruction[def::trimLen++]=vector<string>{"addiu",command[1],"$zero", command[2]};
    }
    else{
        int16_t lowerBits=number;
        int16_t higherBits=(number>>16);

        def::mapPseudo[def::trimLen].first=command;
        def::mapPseudo[def::trimLen].second=2;

        def::trimmedInstruction[def::trimLen++]=vector<string>{"lui","$at", to_string(higherBits)};
        def::trimmedInstruction[def::trimLen++]=vector<string>{"ori",command[1],"$at",to_string(lowerBits)};
    }
}
void moveExtension(vector<string>command){
    def::mapPseudo[def::trimLen].first=command;
    def::mapPseudo[def::trimLen].second=1;

    def::trimmedInstruction[def::trimLen++]=vector<string>{"add",command[1],"$zero", command[2]};
}

void oriExtension(vector<string>command){
    int number=stoi(command[3]);
    if(number<65536 && number>=0){
        def::mapPseudo[def::trimLen].first=command;
        def::mapPseudo[def::trimLen].second=1;

        def::trimmedInstruction[def::trimLen++]=vector<string>{"ori",command[1],command[2]};
    }
    else{
        int16_t lowerBits=number;
        int16_t higherBits=(number>>16);

        def::mapPseudo[def::trimLen].first=command;
        def::mapPseudo[def::trimLen].second=3;

        def::trimmedInstruction[def::trimLen++]=vector<string>{"lui","$at",to_string(higherBits)};
        def::trimmedInstruction[def::trimLen++]=vector<string>{"ori","$at","$at", to_string(lowerBits)};
        def::trimmedInstruction[def::trimLen++]=vector<string>{"or",command[1],command[2],"$at"};
    }
}
void sgtExtension(vector<string>command){
    def::mapPseudo[def::trimLen].first=command;
    def::mapPseudo[def::trimLen].second=1;
    def::trimmedInstruction[def::trimLen++]=vector<string>{"slt",command[1],command[3],command[2]};
}
void bltExtension(vector<string>command){
    def::mapPseudo[def::trimLen].first=command;
    def::mapPseudo[def::trimLen].second=2;

    def::trimmedInstruction[def::trimLen++]=vector<string>{"slt","$at",command[1],command[2]};
    def::trimmedInstruction[def::trimLen++]=vector<string>{"bne","$at","$zero",command[3]};
}
void bgtExtension(vector<string>command){
    def::mapPseudo[def::trimLen].first=command;
    def::mapPseudo[def::trimLen].second=2;

    def::trimmedInstruction[def::trimLen++]=vector<string>{"slt","$at",command[2], command[1]};
    def::trimmedInstruction[def::trimLen++]=vector<string>{"bne","$at","$zero",command[3]};
}

void extension(vector<string>command){
    initialize();
    switch (strToEnum[command[0]])
    {
        case ABS:
            absExtension(command);
            break;
        case LI:
            liExtension(command);
            break;
        case MOVE:
            moveExtension(command);
            break;
        case ORI:
            oriExtension(command);
            break;
        case SGT:
            sgtExtension(command);
            break;
        case BLT:
            bltExtension(command);
            break;
        case BGT:
            bgtExtension(command);
            break;
        default:
            break;
    }
}
#endif