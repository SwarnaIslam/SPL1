#ifndef DEFINITION_H
#define DEFINITION_H
#include<vector>
#include"Algorithm.h"
#include"Math.h"
#define CAPACITY 10009

using namespace std;
int k=0;
struct pseudoTranslate{
    vector<string>first;
    int second=0;
};
namespace def{
    int PC=0;
    int numberOfInstruction=0;
    int dataStart=0;
    int textStart=0;
    int dataEnd=0;
    int textEnd=0;
    int trimLen=0;
    
    vector<string>trimmedInstruction[10000];
    vector<int>Memory;
    BST<string,int> *operators;
    BST<string, int>*detectLabel=NULL;
    dataHashTable* dataTable;
    textHashTable* textTable;
    map<int, struct pseudoTranslate>mapPseudo;
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
        if(tempRegister[i]=="$sp"){
            registers[hashValue].value=0x15f6e100 ;
            continue;
        }
        registers[hashValue].value=0;
    }

}
void defineOperators(){
    vector<string>tempOperators{"li","lui","la","lw","add","sub","subu","addi","mul","mult","mflo","mfhi","div","sll","sllv","srl","srlv","sra","srav","and","or","ori","not","xor","nor","abs","andi","j","jal","bne","beq","blt","bgt","move","syscall","slt","slti","sltu","sgt","j","jal","jr"};
    BST<string, int>*temp=NULL;
    for(string op: tempOperators){

        temp=temp->insertBST(op,-1,temp);
    }
    def::operators=temp;
}

void defineNumberOfInstruction(int lineOfCode){
    def::numberOfInstruction=lineOfCode;
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
    def::dataEnd=sectionEndIndex(def::dataStart,def::textStart);
    def::textEnd=sectionEndIndex(def::textStart,def::dataStart);
}



void define(int LOC){
    defineNumberOfInstruction(LOC);
	defineRegisters();
	defineOperators();
	def::Memory.resize(100000000);

    
}

#endif