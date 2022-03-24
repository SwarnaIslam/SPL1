#ifndef RTYPE_H
#define RTYPE_H
#include<iostream>
#include"definition.h"
#include"format.h"
using namespace std;
enum SysCode{
    printInt=1,
    scanInt=5,
    hexOfInt=34
};
void checkValidReg(long long hashOfRd, long long hashOfRs,long long hashOfRt, string instructionLine){
    checkValidDestination(hashOfRd,instructionLine);
    checkValidSource(hashOfRs,instructionLine);
    checkValidSource(hashOfRt,instructionLine);
}
void syscall(vector<string>command,string instructionLine){
    string input;
    long long hashValue=getHashValue("$v0");
    int32_t val=registers[hashValue].value;
    switch (val)
    {
    case printInt:
        hashValue=getHashValue("$a0");
        val=registers[hashValue].value;
        cout<<"Printing integer: ";
        cout<<val<<"\n\n";
        break;
    case scanInt:
        cout<<"Enter a integer: ";
        cin>>input;
        checkValidInteger(input);
        hashValue=getHashValue("$v0");
        registers[hashValue].value=stoi(input);
        cout<<"Stored input into $v0 register.\n\n";
        break;
    case hexOfInt:
        hashValue=getHashValue("$a0");
        val=registers[hashValue].value;
        cout<<"Printing integer in hexadecimal form: ";
        printf("%X\n\n",val);
        break;
    default:
        reportAndExit("Invalid system call",instructionLine);
        break;
    }
}
void add(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    checkValidReg(hashOfRd,hashOfRs,hashOfRt,instructionLine);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    checkValidInteger(to_string((long long)valRs+(long long)valRt));
    //cout<<to_string((long long)valRs+(long long)valRt)<<endl;
    registers[hashOfRd].value=valRs+valRt;
}
void mul(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    checkValidReg(hashOfRd,hashOfRs,hashOfRt,instructionLine);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int32_t valRd=valRs*valRt;
    registers[hashOfRd].value=valRd;
    //cout<<"Multiplication: "<<valRd<<endl;
}

void mult(vector<string>command,string instructionLine){
    //cout<<"Entered mult:"<<endl;
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRs=getHashValue(command[1]);
    long long hashOfRt=getHashValue(command[2]);

    checkValidSource(hashOfRs,instructionLine);
    checkValidSource(hashOfRt,instructionLine);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;

    int64_t result=(int64_t)valRs*(int64_t)valRt;

    LO.regName="$LO";
    LO.value=result;

    HI.regName="$HI";
    HI.value=(result>>32);

    //cout<<LO.value<<" "<<HI.value<<endl;
}
void div(vector<string>command,string instructionLine){
    //cout<<"Entered mult:"<<endl;
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRs=getHashValue(command[1]);
    long long hashOfRt=getHashValue(command[2]);

    checkValidSource(hashOfRs,instructionLine);
    checkValidSource(hashOfRt,instructionLine);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;


    LO.regName="$LO";
    LO.value=valRs/valRt;

    HI.regName="$HI";
    HI.value=valRs%valRt;

    //cout<<LO.value<<" "<<HI.value<<endl;
}

void mflo(vector<string>command,string instructionLine){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);

    checkValidDestination(hashOfRd,instructionLine);

    int32_t valLo=LO.value;
    registers[hashOfRd].value=valLo;
}
void mfhi(vector<string>command,string instructionLine){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);

    checkValidDestination(hashOfRd,instructionLine);

    int32_t valHI=HI.value;
    registers[hashOfRd].value=valHI;
}
void sll(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    checkValidDestination(hashOfRd,instructionLine);
    checkValidSource(hashOfRs,instructionLine);

    checkValidInteger(command[3]);
    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs<<shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
void sllv(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    checkValidReg(hashOfRd,hashOfRs,hashOfRt,instructionLine);

    int shift_amount=registers[hashOfRt].value;
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs<<shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
void srl(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    checkValidDestination(hashOfRd,instructionLine);
    checkValidSource(hashOfRs,instructionLine);

    checkValidInteger(command[3]);
    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs>>shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
void srlv(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    checkValidReg(hashOfRd,hashOfRs,hashOfRt,instructionLine);

    int shift_amount=registers[hashOfRt].value;
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs>>shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
#endif