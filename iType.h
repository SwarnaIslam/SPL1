#ifndef ITYPE_H
#define ITYPE_H
#include<iostream>
#include"definition.h"
#include"format.h"
#include "Math.h"
#include"psedo.h"
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
    int32_t valImm=stoi(tempNumber);
    checkValid32BitInteger(to_string((long long)valRs+(long long)valImm));
    //cout<<to_string((long long)valRs+(long long)valImm)<<endl;
    registers[hashOfRd].value=valRs+valImm;
}
void li(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValid32BitInteger(command[2]);
    
    int32_t valImm=stoi(command[2]);
    extension(command);

    long long hashOfRd=getHashValue(command[1]);
    checkValidDestination(hashOfRd);
    registers[hashOfRd].value=valImm;
    //cout<<"End of executing li"<<endl;
    
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
    int16_t valRs=registers[hashOfRs].value;
    int16_t valImm=stoi(command[3]);

    int16_t valRd=userDefinedAnd(valRs,valImm);
    registers[hashOfRd].value=valRd;
}
void ori(vector<string>command){
    // cout<<"entered ori"<<endl;
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    checkValid32BitInteger(command[3]);
    checkValidDestination(hashOfRd);
    checkValidSource(hashOfRs);
    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stoi(command[3]);
    extension(command);
    int32_t valRd=userDefinedOr(valRs,valImm);
    registers[hashOfRd].value=valRd;
}
void lui(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    long long hashOfRd=getHashValue(command[1]);
    checkValid16BitInteger(command[2]);

    checkValidDestination(hashOfRd);
    int32_t valImm=stoi(command[2]);
    int32_t valRd=valImm<<16;
    registers[hashOfRd].value=valRd;
}
#endif