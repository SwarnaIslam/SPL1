#ifndef DISPLAY_H
# define DISPLAY_H
#include"Algorithm.h"
#include"definition.h"
void displayStack(){
    long long hashOfSp=getHashValue("$sp");
    long long currStack=registers[hashOfSp].value-0x10010000;
    cout<<"Displaying in top to bottom manner:"<<endl;
    for(long long i=currStack/4;i<(0x15f6e100-0x10010000)/4;i++){
        printf("Address: %#x, value: ",i*4+0x10010000);
        printf("%#x\n",def::Memory[i]);
    }
}
void displayRegisters(){
    vector<string>tempRegister{"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
    for(int i=0;i<tempRegister.size()/2;i++){
        long long hashValue=getHashValue(tempRegister[i]);
        printf("[%s]: %#x\t",tempRegister[i].c_str(),registers[hashValue].value);

        hashValue=getHashValue(tempRegister[i+16]);
        printf("[%s]: %#x\n",tempRegister[i+16].c_str(),registers[hashValue].value);
    }
}
void display(){
    displayRegisters();
    displayStack();
}
#endif