#ifndef OPERATOR_H
#define OPERATOR_H
#include"format.h"
#include"definition.h"
#include"rType.h"
#include"iType.h"
#include"Algorithm.h"
void move(vector<string>command,string instructionLine){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    cout<<"Performing pseudo instruction..."<<endl;
    cout<<command[0]<<" "<<command[1]<<" "<<command[2]<<endl;
    cout<<endl;
    cout<<"Details of this operation:"<<endl;
    cout<<"add"<<" "<<command[1]<<" "<<"$zero"<<" "<<command[2]<<endl;
    registers[hashOfRd].value=registers[hashOfRs].value;
}
void perform(long long hashOfOp,vector<string>command,string instructionLine){
    if(hashOfOp==getHashValue("move")){
        move(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("li")){
        //cout<<"entered if li"<<endl;
        li(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("syscall")){
        syscall(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("add")){
        add(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("addi")){
        addi(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("mul")){
        mul(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("mult")){
        mult(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("div")){
        div(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("mflo")){
        mflo(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("mfhi")){
        mfhi(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("sll")){
        sll(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("sllv")){
        sllv(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("srl")){
        srl(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("srlv")){
        srlv(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("sra")){
        sra(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("srav")){
        srav(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("and")){
        And(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("or")){
        Or(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("not")){
        Not(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("xor")){
        Xor(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("nor")){
        Nor(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("andi")){
        andi(command,instructionLine);
    }
}
void executeInstruction(vector<string>trimmedInstruction[]){
    int textStart=getTextIndex();
    int dataStart=getDataIndex();
    int textEnd=0;
    string instructionLine="";
    BST<string,int>*labels=getTextLabel();
    if(dataStart<textStart){
        textEnd=getNumberOfInstruction();
    }
    else{
        if(dataStart==textStart+1){
            return;
        }
        else{
            textEnd=dataStart;
        }
    }
    for(int i=textStart+1;i<textEnd;i++){
        string tempOperator=trimmedInstruction[i][0];
        if(tempOperator==""){
            continue;
        }
        //cout<<tempOperator<<endl;
        vector<string>operators{"li","la","add","addi","mul","mult","mflo","mfhi","div","sll","sllv","srl","srlv","sra","srav","and","or","not","xor","nor","andi","j","jal","bne","beq","move","syscall"};
        bool operatorFound=false;
        int instructionNum=0;
        long long hashOfTempOp=getHashValue(tempOperator);
        instructionLine=to_string(i+1);
        for(int j=0;j<operators.size();j++){
            long long hashOfOp=getHashValue(operators[j]);
            if(hashOfOp==hashOfTempOp){
                operatorFound=true;
                instructionNum=j;
                break;
            }
        }
        int labelFound=tempOperator.find(':');
        if(labelFound>0&&labelFound<tempOperator.size()){
            tempOperator=tempOperator.substr(0,labelFound);
        }
        if(operatorFound==false&&labels->searchBST(labels,tempOperator)==0){
            reportAndExit("Invalid operation in text section",instructionLine);
        }
        else{
            perform(hashOfTempOp,trimmedInstruction[i],to_string(i+1));
        }
        
    }
}
#endif