#ifndef DEFINITION_H
#define DEFINITION_H
#include<vector>
#include"debugger.h"
using namespace std;
int numberOfInstruction;
int dataIndex,textIndex;
vector<string>keywords;
vector<string>registers;
map<string,int>dataLabel;
map<string,int>textLabel;
void setDataLabel(string labelName,int line){
    dataLabel[labelName]=line;
}
void setTextLabel(string labelName,int line){
    textLabel[labelName]=line;
}
map<string,int>getDataLabel(){
    return dataLabel;
}
map<string,int>getTextLabel(){
    return textLabel;
}
void defineKeywords(){
    vector<string>tempKeywords{"li","la","add","addi","mul","div","j","jal","bne","beq","move","syscall",".data",".text",".word"};
    for(int i=0;i<tempKeywords.size();i++){
        keywords.push_back(tempKeywords[i]);
    }
}
vector<string> getKeywords(){
    return keywords;
}
void defineRegisters(){
    vector<string>tempRegister{"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
    for(int i=0;i<tempRegister.size();i++){
        keywords.push_back(tempRegister[i]);
    }
}
vector<string> getRegisters(){
    return registers;
}
void defineNumberOfInstruction(int lineOfCode){
    numberOfInstruction=lineOfCode;
}
int getNumberOfInstruction(){
    return numberOfInstruction;
}
int defineDataIndex(vector<string>trimmedInstruction[]){
    int i=0;
    int dataFlag=0;
    int dataLine=-1;
    string isData=".data";
    //cout<<"loc:"<<numberOfInstruction<<endl;
    for(i=0;i<numberOfInstruction;i++){
        //cout<<trimmedInstruction[i][0]<<endl;
        if(trimmedInstruction[i][0]!=""){
            if(dataFlag==1&&trimmedInstruction[i][0].c_str()==isData){
                reportAndExit("More than one .data have been found!");
            }
            if(trimmedInstruction[i][0].c_str()==isData){
                dataFlag=1;
                dataLine=i;
            }
        }
    }
    if(dataFlag==0)
        reportAndExit(".data section not found!");
    return dataLine;
}
int defineTextIndex(vector<string>trimmedInstruction[]){
    int i=0;
    int textFlag=0;
    int textLine=-1;
    string isText=".text";
    for(i=0;i<numberOfInstruction;i++){
        if(textFlag==1&&trimmedInstruction[i][0].c_str()==isText){
            reportAndExit("More than one .text have been found!");
        }
        if(trimmedInstruction[i][0].c_str()==isText){
            textFlag=1;
            textLine=i;
        }
    }
    if(textFlag==0)
        reportAndExit(".text section not found!");
    return textLine;
}
void defineSectionIndex(vector<string>trimmedInstruction[]){
    dataIndex=defineDataIndex(trimmedInstruction);
    //cout<<"success defining data in"<<endl;
    textIndex=defineTextIndex(trimmedInstruction);
    //cout<<"success defining text in"<<endl;
}
int getDataIndex(){
    return dataIndex;
}
int getTextIndex(){
    return textIndex;
}
void define(vector<string>trimmedInstruction[],int lineOfCode){
    defineKeywords();
    //cout<<"success defining op"<<endl;
	defineRegisters();
    //cout<<"success defining reg"<<endl;
    defineNumberOfInstruction(lineOfCode);
    //cout<<"success defining loc"<<endl;
    defineSectionIndex(trimmedInstruction);
    //cout<<"success defining sec in"<<endl;
}

#endif