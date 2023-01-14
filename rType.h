#ifndef RTYPE_H
#define RTYPE_H
#include<iostream>
#include"definition.h"
#include"format.h"
#include"Math.h"
#include"psedo.h"
using namespace std;
enum SysCode{
    printInt=1,
    scanInt=5,
    hexOfInt=34,
    Exit=10
};

void syscall(vector<string>command){
    string input;
    long long hashValue=getHashValue("$v0");
    int32_t val=registers[hashValue].value;
    switch (val)
    {
    case printInt:
        //cout<<"Successful printing"<<endl;
        hashValue=getHashValue("$a0");
        val=registers[hashValue].value;
        cout<<"Printing integer: ";
        cout<<val<<"\n\n";
        break;
    case scanInt:
        cout<<"Enter a integer: ";
        cin>>input;
        checkValid32BitInteger(input);
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
    case Exit:
        exit(0);
        break;
    default:
        reportAndExit("Invalid system call");
        break;
    }
}

void add(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    checkValid32BitInteger(to_string((long long)valRs+(long long)valRt));// overflow trap
    //cout<<to_string((long long)valRs+(long long)valRt)<<endl;
    registers[hashOfRd].value=valRs+valRt;
    //cout<<command[1]<<" "<<registers[hashOfRd].value<<endl<<endl;
}
void addu(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    registers[hashOfRd].value=valRs+valRt;
}
void sub(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    checkValid32BitInteger(to_string((long long)valRs-(long long)valRt));
    int32_t valRd=valRs-valRt;
    
    checkValid32BitInteger(to_string(valRd));
    registers[hashOfRd].value=valRd;
}
void subu(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;

    int32_t valRd=(long long)valRs-(long long)valRt;
    
    checkValid32BitInteger(to_string(valRd));
    registers[hashOfRd].value=valRd;
}
void mul(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int64_t result=(int64_t)valRs*(int64_t)valRt;

    LO.regName="$LO";
    LO.value=result;

    HI.regName="$HI";
    HI.value=(result>>32);

    registers[hashOfRd].value=LO.value;
    //cout<<"Multiplication: "<<valRd<<endl;
}

void mult(vector<string>command){
    long long hashOfRs=getHashValue(command[1]);
    long long hashOfRt=getHashValue(command[2]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;

    int64_t result=(int64_t)valRs*(int64_t)valRt;

    LO.regName="$LO";
    LO.value=result;

    HI.regName="$HI";
    HI.value=(result>>32);

    //cout<<LO.value<<" "<<HI.value<<endl;
}
void div(vector<string>command){
    long long hashOfRs=getHashValue(command[1]);
    long long hashOfRt=getHashValue(command[2]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;


    LO.regName="$LO";
    LO.value=valRs/valRt;

    HI.regName="$HI";
    HI.value=valRs%valRt;

    //cout<<LO.value<<" "<<HI.value<<endl;
}

void mflo(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);

    int32_t valLo=LO.value;
    registers[hashOfRd].value=valLo;
}
void mfhi(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    int32_t valHI=HI.value;
    registers[hashOfRd].value=valHI;
}
void sll(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs<<shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
void sllv(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int shift_amount=registers[hashOfRt].value;
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs<<shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
void srl(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    checkValid32BitInteger(command[3]);
    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    unsigned int valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs>>shift_amount);
    registers[hashOfRd].regName=command[1];                                                                                                                                                                                                                                                                                                                     
}
void srlv(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int shift_amount=registers[hashOfRt].value;
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    unsigned  int valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs>>shift_amount);                                                                                                                                                                                                                                                                                                                      
}
void sra(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    checkValid32BitInteger(command[3]);
    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value; 
    int32_t valOfRd=  (valOfRs>>shift_amount); 
    registers[hashOfRd].value=valOfRd;                                                                                                                                                                                                                                                                                                                
}
void srav(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);
    int shift_amount=registers[hashOfRt].value;

    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    int32_t valOfRs=registers[hashOfRs].value;    
    registers[hashOfRd].value=(valOfRs>>shift_amount);
    registers[hashOfRd].regName=command[1];
    //cout<<"Sll result: "<<registers[hashOfRd].value<<" "<<valOfRs<<endl;                                                                                                                                                                                                                                                                                                                         
}
void And(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int32_t valRd=userDefinedAnd(valRs,valRt);
    registers[hashOfRd].value=valRd;
}

void Or(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int32_t valRd=userDefinedOr(valRs,valRt);
    registers[hashOfRd].value=valRd;
}
int Xor(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int32_t valRd=userDefinedXor(valRs,valRt);
    registers[hashOfRd].value=valRd;
    return valRd;
}
void Nor(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int32_t valRd=userDefinedNor(valRs,valRt);
    registers[hashOfRd].value=valRd;
}
void Not(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRd=userDefinedNot(valRs);
    registers[hashOfRd].value=valRd;
}

void slt(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    int32_t valRd=(valRs<valRt)?1:0;
    
    registers[hashOfRd].value=valRd;
}

void sltu(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);

    long long valRs=getUnsignedNumber(command[2]);
    long long valRt=getUnsignedNumber(command[3]);

    int32_t valRd=(valRs<valRt)?1:0;
    
    registers[hashOfRd].value=valRd;
}

#endif