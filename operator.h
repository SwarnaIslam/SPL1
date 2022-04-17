#ifndef OPERATOR_H
#define OPERATOR_H
#include"format.h"
#include"definition.h"
#include"rType.h"
#include"iType.h"
#include"psedo.h"
#include"Algorithm.h"
void perform(vector<string>command){
    if(command[0]==("move")){
        move(command);
    }
    else if(command[0]==("li")){
        //cout<<"entered if li"<<endl;
        li(command);
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
    else if(command[0]==("abs")){
        abs(command);
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
}
void executeInstruction(){
    
    for(int i=def::textStart+1;i<def::textEnd;i++){
        string tempOperator=def::trimmedInstruction[i][0];
        if(tempOperator==""){
            continue;
        }
    
        bool operatorFound=def::operators->searchBST(def::operators,tempOperator);
        if(operatorFound==true){
            long long hashOfTempOp=getHashValue(tempOperator);
            perform(def::trimmedInstruction[i]);
        }
    }
    if(def::detectLabel!=NULL){
        def::detectLabel->free_children(def::detectLabel);
        free(def::detectLabel);
    }
}
#endif