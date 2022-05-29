#ifndef JTYPE_H
#define JTYPE_H
#include<iostream>
#include<vector>
#include"debugger.h"
#include"Algorithm.h"
using namespace std;
int j(vector<string>command){
    textHashTableItem* item=text_ht_search(def::textTable, command[1]);
    if(item->address<0x00400000){
        reportAndExit("Address out of bound 0x00400000");
    }
    if((item->address-0x00400000)%4){
        reportAndExit("Store address not aligned on word boundary");
    }
    int line=(item->address-0x00400000)/4;
    return line;
}
int jal(vector<string>command, int currIndex){
    textHashTableItem* item=text_ht_search(def::textTable, command[1]);
    int hashOfRd=getHashValue("$ra");
    registers[hashOfRd].value=0x00400000+currIndex*4+4;
    int line=(item->address-0x00400000)/4;
    return line;
}
int jr(vector<string>command){
    int hashOfRs=getHashValue(command[1]);
    if(registers[hashOfRs].value<0x00400000){
        reportAndExit("Address out of bound 0x00400000");
    }
    if((registers[hashOfRs].value-0x00400000)%4){
        reportAndExit("Store address not aligned on word boundary");
    }
    int line=(registers[hashOfRs].value-0x00400000)/4;
    return line;
}
#endif