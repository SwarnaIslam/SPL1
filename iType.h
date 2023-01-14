#ifndef ITYPE_H
#define ITYPE_H
#include<iostream>
#include"definition.h"
#include"format.h"
#include "Math.h"
#include"psedo.h"
using namespace std;
void addi(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    string tempNumber=command[3];
    checkValid16BitInteger(tempNumber);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stoi(tempNumber);
    checkValid32BitInteger(to_string((long long)valRs+(long long)valImm));
    registers[hashOfRd].value=valRs+valImm;
    //cout<<command[1]<<" "<<registers[hashOfRd].value<<endl<<endl;
}
void addiu(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    string tempNumber=command[3];
    checkValid16BitInteger(tempNumber);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stoi(tempNumber);
    //cout<<"addiu: "<<valRs+valImm<<endl;
    registers[hashOfRd].value=valRs+valImm;
}
void andi(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    checkValid16BitInteger(command[3]);
    int16_t valRs=registers[hashOfRs].value;
    int16_t valImm=stoi(command[3]);

    int16_t valRd=userDefinedAnd(valRs,valImm);
    registers[hashOfRd].value=valRd;
}
void ori(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stoi(command[3]);
    int32_t valRd=userDefinedOr(valRs,valImm);
    registers[hashOfRd].value=valRd;
}
void lui(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    int32_t valImm=stoi(command[2]);
    int32_t valRd=valImm<<16;
    registers[hashOfRd].value=valRd;
}
void slti(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    int32_t valRs=abs(registers[hashOfRs].value);
    int32_t valImm=stoi(command[3]);
    int32_t valRd=(valRs<valImm)?1:0;
    
    registers[hashOfRd].value=valRd;
}
int beq(vector<string>command){
    long long hashOfRs=getHashValue(command[1]);
    long long hashOfRt=getHashValue(command[2]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;

    if(valRs==valRt){
        textHashTableItem* tempItem=text_ht_search(def::textTable,command[3]);
        int line=(tempItem->address-0x00400000)/4;
        return line;
    }

    return -1;
}
int bne(vector<string>command){

    long long hashOfRs=getHashValue(command[1]);
    long long hashOfRt=getHashValue(command[2]);
    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    //cout<<valRs<<" "<<valRt<<endl;
    if(valRs!=valRt){
        textHashTableItem* tempItem=text_ht_search(def::textTable,command[3]);
        //cout<<tempItem->address-0x00400000<<endl;
        int line=(tempItem->address-0x00400000)/4;
        //cout<<line<<endl;
        return line;
    }

    return -1;
}

void lw(vector<string>command){
    int base=0;
    int offset=0;
    int hashOfRd=getHashValue(command[1]);
    int openingFound=command[2].find('(');
    int len=command[2].length();
    if(openingFound<len&&openingFound>=0){
        int closingFound=command[2].find(')');

        string tempRegister=command[2].substr(openingFound+1,closingFound-openingFound-1);

        string temp=command[2].substr(0, openingFound);

        dataHashTableItem* item=data_ht_search(def::dataTable,temp);
        int hashOfRs=getHashValue(tempRegister);
        if(item!=NULL){
            base=item->byteAddress;
            offset=registers[hashOfRs].value;
        }
        else{
            offset=stoi(temp);
            base=registers[hashOfRs].value;
        }

    }
    else{
        dataHashTableItem* item=data_ht_search(def::dataTable,command[2]);
        base=item->byteAddress;
    }
    if(base+offset<0x10010000|| base+offset>=0x15f6e100){
        reportAndExit("Address out of bound 0x10010000");
    }
    
    int index=(base+offset)-0x10010000;
    if(index%4){
        reportAndExit("Store address not aligned on word boundary");
    }
    //printf("%#x\n",base+offset);
    index/=4;
    //cout<<index<<" "<<def::Memory[index]<<endl;
    registers[hashOfRd].value=def::Memory[index];
}
void sw(vector<string>command){
    int base=0;
    int offset=0;
    int hashOfRs=getHashValue(command[1]);
    int openingFound=command[2].find('(');
    int len=command[2].length();
    if(openingFound<len&&openingFound>=0){
        int closingFound=command[2].find(')');

        string tempRegister=command[2].substr(openingFound+1,closingFound-openingFound-1);

        string temp=command[2].substr(0, openingFound);

        dataHashTableItem* item=data_ht_search(def::dataTable,temp);
        int hashOfRd=getHashValue(tempRegister);
        if(item!=NULL){
            base=item->byteAddress;
            offset=registers[hashOfRd].value;
        }
        else{
            offset=stoi(temp);
            base=registers[hashOfRd].value;
        }

    }
    else{
        dataHashTableItem* item=data_ht_search(def::dataTable,command[2]);
        base=item->byteAddress;
    }
    if(base+offset<0x10010000||base+offset>=0x15f6e100){
        reportAndExit("Address out of bound 0x10010000");
    }
    
    int index=(base+offset)-0x10010000;
    if(index%4){
        reportAndExit("Store address not aligned on word boundary");
    }

    index/=4;
    def::Memory[index]=registers[hashOfRs].value;

}
void la(vector<string>command){
    dataHashTableItem* item=data_ht_search(def::dataTable,command[2]);
    int hashOfRd=getHashValue(command[1]);
    registers[hashOfRd].value=item->byteAddress;
}

#endif