#ifndef SPLITER_H
#define SPLITER_H
#include<vector>
#include"definition.h"
using namespace std;
int size=0;
void commaRemove(char *untrimmedInstruction){
    int i=0;
    int f=-1;
    for(i=0;i<size;i++){
        if(untrimmedInstruction[i]==','){
            untrimmedInstruction[i]=' ';
        }
    }
}
void commentRemove(char unTrimmedInstruction[]){
    int f=-1;
    for(int i=0;i<size;i++){
        if(unTrimmedInstruction[i]=='#'){
            f=i;
            break;
        }
    }
    if(f<size&&f>=0){
        for(int i=f;i<size;i++){
            unTrimmedInstruction[i]=' ';
        }
    }
}
vector<string>split(char unTrimmedInstruction[],int s,int instructionLine){
    vector<string>trimmedInstruction;
    size=s;
    commentRemove(unTrimmedInstruction);
    commaRemove(unTrimmedInstruction);
    int newLine=1;
    for(int i=0;i<size;i++){
        if(unTrimmedInstruction[i]!=' '&&unTrimmedInstruction[i]!='\0'&&unTrimmedInstruction[i]!='\n'&&unTrimmedInstruction[i]!='\t'&&unTrimmedInstruction[i]!='\r'){
            string temp="";
            newLine=0;
            for(int j=i;j<size;j++){
                if(unTrimmedInstruction[j]!=' '&&unTrimmedInstruction[j]!='\0'&&unTrimmedInstruction[j]!='\n'&&unTrimmedInstruction[j]!='\t'&&unTrimmedInstruction[j]!='\r'){
                    temp.push_back(unTrimmedInstruction[j]);
                }
                else{
                    trimmedInstruction.push_back(temp);
                    i=j;
                    break;
                }
            }
        }
    }
    if(newLine){
        trimmedInstruction.push_back("");
    }
    return trimmedInstruction;
}
void trim(vector<string>instruction){
    int insNumber=0;
	for(int i=0;i<def::numberOfInstruction;i++){
        //cout<<instruction[i]<<endl;
		int InsLength=instruction[i].length()+1;
		char tempIns[InsLength];
		for(int j=0;j<InsLength;j++){
			tempIns[j]=instruction[i][j];
		}
		def::trimmedInstruction[insNumber++]=split(tempIns,InsLength,i);
	}
}
#endif