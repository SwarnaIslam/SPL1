#ifndef DEFINITION_H
#define DEFINITION_H
#include<vector>
#include"Algorithm.h"
#define CAPACITY 10009

using namespace std;
vector<string>keywords;
namespace def{
    int PC=0;
    int numberOfInstruction=0;
    int dataStart=0;
    int textStart=0;
    int dataEnd=0;
    int textEnd=0;
    vector<string>trimmedInstruction[1000];
    BST<string,int> *operators;
    BST<string, int>*detectLabel;
    dataHashTable* dataTable;
    textHashTable* textTable;
}
struct Reg{
    string regName="";
    int32_t value=0;
};
Reg registers[200000];
Reg LO, HI;


vector<string> getKeywords(){
    return keywords;
}
void defineRegisters(){
    vector<string>tempRegister{"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
    for(int i=0;i<tempRegister.size();i++){
        long long hashValue=getHashValue(tempRegister[i]);
        registers[hashValue].regName=tempRegister[i];
        registers[hashValue].value=0;
    }
}
void defineOperators(){
    vector<string>tempOperators{"li","la","add","sub","addi","mul","mult","mflo","mfhi","div","sll","sllv","srl","srlv","sra","srav","and","or","not","xor","nor","abs","andi","j","jal","bne","beq","move","syscall"};
    BST<string, int>*temp=NULL;
    for(string op: tempOperators){

        temp=temp->insertBST(op,-1,temp);
    }
    def::operators=temp;
}

void defineNumberOfInstruction(int lineOfCode){
    def::numberOfInstruction=lineOfCode;
}

int defineDataStart(){
    int i=0;
    int dataFlag=0;
    int dataLine=-1;
    string isData=".data";
    
    for(i=0;i<def::numberOfInstruction;i++){
    
        if(def::trimmedInstruction[i][0]!=""){
            if(dataFlag== 1 && def::trimmedInstruction[i][0].c_str()==isData){
                cout<<"More than one .data have been found!"<<endl;
                exit(1);
            }
            if(def::trimmedInstruction[i][0].c_str()==isData){
                dataFlag=1;
                dataLine=i;
            }
        }
    }
    if(dataFlag==0){
        cout<<".data section not found!"<<endl;
        exit(1);
    }
    return dataLine;
}
int defineTextStart(){
    int i=0;
    int textFlag=0;
    int textLine=-1;
    string isText=".text";
    for(i=0;i<def::numberOfInstruction;i++){
        if(textFlag== 1 && def::trimmedInstruction[i][0].c_str()==isText){
            cout<<"More than one .text have been found!"<<endl;
            exit(1);
        }
        if(def::trimmedInstruction[i][0].c_str()==isText){
            textFlag=1;
            textLine=i;
        }
    }
    if(textFlag==0){
        cout<<".text section not found!"<<endl;
        exit(1);
    }
    return textLine;
}
int sectionEndIndex(int start1, int start2){
    int end=-1;
    if(start1>start2){
        end=def::numberOfInstruction;
    }
    else{
        if(start1+1==start2){
            return end;
        }
        else{
            end=start2;
        }
    }
    return end;
}
void defineSectionIndex(){
    def::dataStart=defineDataStart();
    def::textStart=defineTextStart();

    def::dataEnd=sectionEndIndex(def::dataStart,def::textStart);
    def::textEnd=sectionEndIndex(def::textStart,def::dataStart);
}
void define(){
    def::textTable=createtextHashTable(CAPACITY);
    //cout<<"success defining op"<<endl;
	defineRegisters();
    defineOperators();
    //cout<<"success defining reg"<<endl;
    //cout<<"success defining loc"<<endl;
    defineSectionIndex();
    //cout<<"success defining sec in"<<endl;
}

#endif