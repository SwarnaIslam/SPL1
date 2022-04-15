#ifndef OPERATOR_H
#define OPERATOR_H
#include"format.h"
#include"definition.h"
#include"rType.h"
#include"iType.h"
#include"Algorithm.h"
void move(vector<string>command){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    cout<<"Performing pseudo instruction..."<<endl;
    cout<<command[0]<<" "<<command[1]<<" "<<command[2]<<endl;
    cout<<endl;
    cout<<"Details of this operation:"<<endl;
    cout<<"add"<<" "<<command[1]<<" "<<"$zero"<<" "<<command[2]<<endl;
    registers[hashOfRd].value=registers[hashOfRs].value;
}
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
    
    for(def::PC=def::textStart+1;def::PC<def::textEnd;def::PC++){
        string tempOperator=def::trimmedInstruction[def::PC][0];
        if(tempOperator==""){
            continue;
        }
    
        int labelFound=tempOperator.find(':');
        bool operatorFound=(def::operators->searchBST(def::operators,tempOperator)!=0)?true:false;
        if(labelFound>0&&labelFound<tempOperator.size()){
            tempOperator=tempOperator.substr(0,labelFound);
        }
        if(operatorFound==false&& text_ht_search(def::textTable,tempOperator)==NULL){
            reportAndExit("Invalid operation in text section");
        }
        else{
            long long hashOfTempOp=getHashValue(tempOperator);
            perform(hashOfTempOp,def::trimmedInstruction[def::PC]);
        }
        
    }
}
#endif