#ifndef DEFINITION_H
#define DEFINITION_H
#include<vector>
#include"Algorithm.h"
#include"Math.h"
#define CAPACITY 10009

using namespace std;
int k=0;

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

void defineRegisters(){
    vector<string>tempRegister{"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};
    for(int i=0;i<tempRegister.size();i++){
        long long hashValue=getHashValue(tempRegister[i]);
        registers[hashValue].regName=tempRegister[i];
        registers[hashValue].value=0;
    }
}
void defineOperators(){
    vector<string>tempOperators{"li","lui","la","add","sub","subu","addi","mul","mult","mflo","mfhi","div","sll","sllv","srl","srlv","sra","srav","and","or","ori","not","xor","nor","abs","andi","j","jal","bne","beq","move","syscall"};
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

void nextInstruction(int currInd){
    string op=def::trimmedInstruction[currInd][0];
    if(op=="li"){
        string tempNumber=def::trimmedInstruction[currInd][2];
        checkValid32BitInteger(tempNumber);
        int number=stoi(tempNumber);
        if(number<=32767 && number>=-32768){
            k++;
        }
        else{
            k+=2;
        }
    }
    else if(op=="abs"){
        k+=3;
    }
    else if(op=="ori"){
        string tempNumber=def::trimmedInstruction[currInd][3];
        checkValid32BitInteger(tempNumber);
        int number=stoi(tempNumber);
        if(number<65536 && number>=0){
            k++;
        }
        else{
            k+=2;
        }
    }
    else{
        k++;
    }
}
void defineProgramCounter(){
    def::textTable=createtextHashTable(CAPACITY);
    for(int i=def::textStart+1;i<def::textEnd;i++){
        string tempInstruction=def::trimmedInstruction[i][0];
        if(tempInstruction==""){
            continue;
        }
    
        int labelFound=tempInstruction.find(':');
        bool operatorFound=def::operators->searchBST(def::operators,tempInstruction);
        if(labelFound>0&&labelFound<tempInstruction.size()){
            tempInstruction=tempInstruction.substr(0,labelFound);
        }
        bool flag=def::detectLabel->searchBST(def::detectLabel, tempInstruction);
        if(flag==true){
            int j=i+1;
            if(j<def::textEnd){
                string op=def::trimmedInstruction[j][0];
                while(j<def::textEnd && def::operators->searchBST(def::operators, op)==0)j++;
                text_ht_insert(def::textTable,tempInstruction,k,j);
            }
        }
        else if(operatorFound==false){
            reportAndExit("Invalid operation in text section",i);
        }
        else{
            nextInstruction(i);
        }
    }
    print_text_table(def::textTable);
}
void define(){
	defineRegisters();
    //cout<<"success defining reg"<<endl;
    defineOperators();
    //cout<<"success defining op"<<endl;
    defineSectionIndex();
    //cout<<"success defining sec in"<<endl;
    //defineProgramCounter();

}

#endif