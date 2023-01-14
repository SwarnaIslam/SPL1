#ifndef PREPROCESS_H
#define PREPROCESS_H
#include<vector>
#include"rTypePreprocess.h"
#include"iTypePreprocess.h"
#include"jTypePreprocessor.h"
using namespace std;
int preprocess(vector<string>command){
    //cout<<"Preprocess"<<endl;
    if(command[0]==("move")){
        movePre(command);
    }
    else if(command[0]==("li")){
        //cout<<"Li preprocess"<<endl;
        liPre(command);
    }
    else if(command[0]==("syscall")){
        syscallPre(command);
    }
    else if(command[0]==("add")||command[0]=="mul"||command[0]=="sllv"||command[0]=="srlv"||command[0]=="srav"||command[0]=="and"||command[0]=="or"||command[0]=="xor"||command[0]=="nor"||command[0]=="sub"||command[0]=="subu"||command[0]=="slt"||command[0]=="sltu"){
        generalPurposePre(command);
    }
    else if(command[0]=="sgt"){
        sgtPre(command);
    }
    else if(command[0]==("addi")){
        addiPre(command);
    }
    else if(command[0]==("mult")){
        multPre(command);
    }
    else if(command[0]==("div")){
        divPre(command);
    }
    else if(command[0]==("mflo")){
        mfloPre(command);
    }
    else if(command[0]==("mfhi")){
        mfhiPre(command);
    }
    else if(command[0]==("sll")){
        sllPre(command);
    }
    else if(command[0]==("srl")){
        srlPre(command);
    }
    else if(command[0]==("sra")){
        sraPre(command);
    }
    else if(command[0]==("not")){
        NotPre(command);
    }
    else if(command[0]==("andi")){
        andiPre(command);
    }
    else if(command[0]==("abs")){
        absPre(command);
    }
    else if(command[0]==("ori")){
        oriPre(command);
    }
    else if(command[0]=="lui"){
        luiPre(command);
    }
    else if(command[0]==("slti")){
        sltiPre(command);
    }
    else if(command[0]=="lw"){
        lwPre(command);
    }
    else if(command[0]=="sw"){
        swPre(command);
    }
    else if(command[0]=="beq"){
        beqPre(command);
    }
    else if(command[0]=="bne"){
        bnePre(command);
    }
    else if(command[0]=="blt"){
        bltPre(command);
        
    }
    else if(command[0]=="bgt"){
        bgtPre(command);
        
    }
    else if(command[0]=="la"){
        laPre(command);
    }
    else if(command[0]=="jal"){
        jalPre(command);
    }
    else if(command[0]=="j"){
        jPre(command);
    }
    else if(command[0]=="jr"){
        jrPre(command);
    }
    else{
        //cout<<"Here"<<endl;
        reportAndExit("Invalid operation");
    }
}
#endif