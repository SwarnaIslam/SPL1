#ifndef OPERATOR_H
#define OPERATOR_H
#include"format.h"
#include"display.h"
#include"definition.h"
#include"rType.h"
#include"iType.h"
#include"jType.h"
int perform(vector<string>command, int currLine){
    if(command[0]==("move")){
        move(command);
    }
    else if(command[0]==("syscall")){
        syscall(command);
    }
    else if(command[0]==("add")){
        add(command);
    }
    else if(command[0]==("addi")){
        addi(command);
    }
    else if(command[0]==("addiu")){
        addiu(command);
    }
    else if(command[0]==("mul")){
        mul(command);
    }
    else if(command[0]==("mult")){
        mult(command);
    }
    else if(command[0]==("div")){
        div(command);
    }
    else if(command[0]==("mflo")){
        mflo(command);
    }
    else if(command[0]==("mfhi")){
        mfhi(command);
    }
    else if(command[0]==("sll")){
        sll(command);
    }
    else if(command[0]==("sllv")){
        sllv(command);
    }
    else if(command[0]==("srl")){
        srl(command);
    }
    else if(command[0]==("srlv")){
        srlv(command);
    }
    else if(command[0]==("sra")){
        sra(command);
    }
    else if(command[0]==("srav")){
        srav(command);
    }
    else if(command[0]==("and")){
        And(command);
    }
    else if(command[0]==("or")){
        Or(command);
    }
    else if(command[0]==("not")){
        Not(command);
    }
    else if(command[0]==("xor")){
        Xor(command);
    }
    else if(command[0]==("nor")){
        Nor(command);
    }
    else if(command[0]==("andi")){
        andi(command);
    }
    else if(command[0]==("sub")){
        sub(command);
    }
    else if(command[0]==("ori")){
        ori(command);
    }
    else if(command[0]=="lui"){
        lui(command);
    }
    else if(command[0]=="subu"){
        subu(command);
    }
    else if(command[0]==("slt")){
        slt(command);
    }
    else if(command[0]==("slti")){
        slti(command);
    }
    else if(command[0]=="sltu"){
        sltu(command);
    }
    else if(command[0]=="lw"){
        lw(command);
    }
    else if(command[0]=="sw"){
        sw(command);
    }
    else if(command[0]=="beq"){
        int newLine = beq(command);
        if(newLine>=0){
            newLine--;
            return newLine;
        }
    }
    else if(command[0]=="bne"){
        int newLine = bne(command);
        if(newLine>=0){
            //cout<<newLine<<endl;
            newLine--;
            return newLine;
        }
    }
    else if(command[0]=="la"){
        la(command);
    }
    else if(command[0]=="jal"){
        int newLine = jal(command,currLine);
        if(newLine>=0){
            newLine--;
            return newLine;
        }
    }
    else if(command[0]=="j"){
        int newLine = j(command);
        if(newLine>=0){
            newLine--;
            return newLine;
        }
    }
    else if(command[0]=="jr"){
        int newLine = jr(command);
        if(newLine>=0){
            newLine--;
            return newLine;
        }
    }
    else{
        reportAndExit("Unknown operation");
    }
    return currLine;
}
void executeInstruction(){
    
    for(int i=0;i<def::trimLen;i++){
        //cout<<def::trimmedInstruction[i].size()<<endl;
        getchar();
        if(def::mapPseudo[i].second!=0){
            cout<<"The next "<<def::mapPseudo[i].second<<" instruction(s) is/are the translation(s) of: ";
            for(int j=0;j<def::mapPseudo[i].first.size();j++){
                cout<<def::mapPseudo[i].first[j]<<" ";
            }
            cout<<endl;
        }
        cout<<"PC: ";
        printf("%#x\n", 0x00400000+i*4);
        for(int j=0;j<def::trimmedInstruction[i].size();j++){
            cout<<def::trimmedInstruction[i][j]<<" ";
        }
        cout<<endl;
        i=perform(def::trimmedInstruction[i],i);
        display();
    }
    if(def::detectLabel!=NULL){
        def::detectLabel->free_children(def::detectLabel);
        free(def::detectLabel);
    }
}
#endif