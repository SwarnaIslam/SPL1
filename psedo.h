#ifndef PSEUDO_H
#define PSEUDO_H
#include<iostream>
#include<vector>
#include<map>
#include"format.h"
using namespace std;
enum Instructions{
    ABS, LI, MOVE, LW, ORI, SGT,BLT, BGT
};
map<string, Instructions>strToEnum;
void initialize(){
    strToEnum["move"]=MOVE;
    strToEnum["li"]=LI;
    strToEnum["abs"]=ABS;
    strToEnum["lw"]=LW;
    strToEnum["ori"]=ORI;
    strToEnum["sgt"]=SGT;
    strToEnum["blt"]=BLT;
    strToEnum["bgt"]=BGT;
}
void absExtension(vector<string>command){

    cout<<"sra "<<"$at"<<" "<<command[2]<<" "<<31<<endl;
    cout<<"xor "<<command[1]<<" "<<command[2]<<" "<<"$at"<<endl;
    cout<<"subu "<<command[1]<<" "<<command[1]<<" "<<"$at"<<endl;
}

void liExtension(vector<string>command){
    int number=stoi(command[2]);
    if(number<=32767 && number>=-32768){
        cout<<"addiu "<<command[1]<<" $0 "<<command[2]<<endl;
    }
    else{
        int16_t lowerBits=number;
        int16_t higherBits=(number>>16);

        printf("lui $at %#x\n",higherBits);
        printf("ori %s $at %#x\n",command[1].c_str(),lowerBits);
    }
}
void moveExtension(vector<string>command){
    cout<<"add"<<" "<<command[1]<<" "<<"$zero"<<" "<<command[2]<<endl;
}

void oriExtension(vector<string>command){
    int number=stoi(command[3]);
    if(number<65536 && number>=0){
        cout<<"ori "<<command[1]<<" "<<command[2]<<endl;
    }
    else{
        int16_t lowerBits=number;
        int16_t higherBits=(number>>16);

        printf("lui $at %#x\n",higherBits);
        printf("ori $at $at %#x\n",lowerBits);
        cout<<"or "<<command[1]<<" "<<command[2]<<" $at"<<endl;
    }
}
void sgtExtension(vector<string>command){
    cout<<"slt"<<" "<<command[1]<<" "<<command[3]<<" "<<command[2]<<endl;
}
void bltExtension(vector<string>command){
    cout<<"slt"<<" $at "<<command[1]<<" "<<command[2]<<endl;
    cout<<"bne $at $zero "<<command[3]<<endl;
}
void bgtExtension(vector<string>command){
    cout<<"slt"<<" $at "<<command[2]<<" "<<command[1]<<endl;
    cout<<"bne $at $zero "<<command[3]<<endl;
}
void extension(vector<string>command){
    initialize();
    cout<<"Performing pseudo instruction..."<<endl;
    for(string token: command){
        cout<<token<<" ";
    }
    cout<<endl<<endl;

    cout<<"Details of this operation:"<<endl;
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
    cout<<endl;
}
#endif