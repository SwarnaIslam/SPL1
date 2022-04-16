#ifndef ITYPE_H
#define ITYPE_H
#include<iostream>
#include"definition.h"
#include"format.h"
#include "Math.h"
using namespace std;
void addi(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    long long hashOfRd=getHashValue(command[1]);
    checkValidDestination(hashOfRd);

    long long hashOfRs=getHashValue(command[2]);
    checkValidSource(hashOfRs);

    string tempNumber=command[3];
    checkValid16BitInteger(tempNumber);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stol(tempNumber);
    checkValid32BitInteger(to_string((long long)valRs+(long long)valImm));
    //cout<<to_string((long long)valRs+(long long)valImm)<<endl;
    registers[hashOfRd].value=valRs+valImm;
}
void li(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValid32BitInteger(command[2]);
    
    int32_t number=stoi(command[2]);
    extension(command);

    long long hashOfRd=getHashValue(command[1]);
    checkValidDestination(hashOfRd);
    registers[hashOfRd].value=number;
    
}
void andi(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    long long hashOfRd=getHashValue(command[1]);
    checkValidDestination(hashOfRd);

    long long hashOfRs=getHashValue(command[2]);
    checkValidSource(hashOfRs);

    checkValid16BitInteger(command[3]);
    int16_t val1=registers[hashOfRs].value;
    int16_t val2=stoi(command[3]);

    int16_t valRd=userDefinedAnd(val1,val2);
    registers[hashOfRd].value=valRd;
}
#endif