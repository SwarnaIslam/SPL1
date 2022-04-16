#ifndef OPERATOR_H
#define OPERATOR_H
#include"format.h"
#include"definition.h"
#include"rType.h"
#include"iType.h"
#include"Algorithm.h"
void perform(long long hashOfOp,vector<string>command){
    if(hashOfOp==getHashValue("move")){
        move(command);
    }
    else if(hashOfOp==getHashValue("li")){
        //cout<<"entered if li"<<endl;
        li(command);
    }
    else if(hashOfOp==getHashValue("syscall")){
        syscall(command);
    }
    else if(hashOfOp==getHashValue("add")){
        add(command);
    }
    else if(hashOfOp==getHashValue("addi")){
        addi(command);
    }
    else if(hashOfOp==getHashValue("mul")){
        mul(command);
    }
    else if(hashOfOp==getHashValue("mult")){
        mult(command);
    }
    else if(hashOfOp==getHashValue("div")){
        div(command);
    }
    else if(hashOfOp==getHashValue("mflo")){
        mflo(command);
    }
    else if(hashOfOp==getHashValue("mfhi")){
        mfhi(command);
    }
    else if(hashOfOp==getHashValue("sll")){
        sll(command);
    }
    else if(hashOfOp==getHashValue("sllv")){
        sllv(command);
    }
    else if(hashOfOp==getHashValue("srl")){
        srl(command);
    }
    else if(hashOfOp==getHashValue("srlv")){
        srlv(command);
    }
    else if(hashOfOp==getHashValue("sra")){
        sra(command);
    }
    else if(hashOfOp==getHashValue("srav")){
        srav(command);
    }
    else if(hashOfOp==getHashValue("and")){
        And(command);
    }
    else if(hashOfOp==getHashValue("or")){
        Or(command);
    }
    else if(hashOfOp==getHashValue("not")){
        Not(command);
    }
    else if(hashOfOp==getHashValue("xor")){
        Xor(command);
    }
    else if(hashOfOp==getHashValue("nor")){
        Nor(command);
    }
    else if(hashOfOp==getHashValue("andi")){
        andi(command);
    }
    else if(hashOfOp==getHashValue("sub")){
        sub(command);
    }
    else if(hashOfOp==getHashValue("abs")){
        abs(command);
    }
}
void executeInstruction(){

    int textEnd=0;
    string instructionLine="";
    
    for(int i=def::textStart+1;i<def::textEnd;i++){
        string tempOperator=def::trimmedInstruction[i][0];
        if(tempOperator==""){
            continue;
        }
    
        int labelFound=tempOperator.find(':');
        bool operatorFound=def::operators->searchBST(def::operators,tempOperator);
        if(labelFound>0&&labelFound<tempOperator.size()){
            tempOperator=tempOperator.substr(0,labelFound);
        }
        bool flag=def::detectLabel->searchBST(def::detectLabel, tempOperator);
        if(operatorFound==false&& flag==false){
            reportAndExit("Invalid operation in text section",i);
        }
        else{
            long long hashOfTempOp=getHashValue(tempOperator);
            perform(hashOfTempOp,def::trimmedInstruction[i]);
        }
        def::detectLabel->free_children(def::detectLabel);
        free(def::detectLabel);
    }
}
#endif