#ifndef ITYPE_H
#define ITYPE_H
#include<iostream>
#include"definition.h"
#include"format.h"
using namespace std;
void addi(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    checkValidDestination(hashOfRd,instructionLine);

    long long hashOfRs=getHashValue(command[2]);
    checkValidSource(hashOfRs,instructionLine);

    string tempNumber=command[3];
    checkValidInteger(tempNumber);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stol(tempNumber);
    checkValidInteger(to_string((long long)valRs+(long long)valImm));
    //cout<<to_string((long long)valRs+(long long)valImm)<<endl;
    registers[hashOfRd].value=valRs+valImm;
}
void li(vector<string>command,string instructionLine){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    checkValidInteger(command[2]);
    cout<<"Performing pseudo instruction..."<<endl;
    cout<<command[0]<<" "<<command[1]<<" "<<command[2]<<endl;
    cout<<endl;
    int32_t number=stoi(command[2]);
    int16_t lowerBits=number;
    int16_t higherBits=(number>>16);

    cout<<"Details of this operation:"<<endl;
    printf("lui $at %X\n",higherBits);
    printf("ori %s $at %X\n\n",command[1].c_str(),lowerBits);

    long long hashOfRd=getHashValue(command[1]);
    checkValidDestination(hashOfRd,instructionLine);
    registers[hashOfRd].value=number;
}

#endif