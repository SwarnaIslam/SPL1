#ifndef JTYPEPREPROCESSOR_H
#define JTYPEPREPROCESSOR_H
#include<iostream>
#include<vector>
#include"debugger.h"
#include"Algorithm.h"
#include"format.h"
using namespace std;
void jPre(vector<string>command){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section");
    }
    if(!isLabel(command[1])){
        reportAndExit("Label not found");
    }
    def::trimmedInstruction[def::trimLen++]=command;
}
void jalPre(vector<string>command){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section");
    }
    if(!isLabel(command[1])){
        reportAndExit("Label not found");
    }
    def::trimmedInstruction[def::trimLen++]=command;
}
void jrPre(vector<string>command){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section");
    }
    checkValidSource(command[1]);
    def::trimmedInstruction[def::trimLen++]=command;
}
#endif