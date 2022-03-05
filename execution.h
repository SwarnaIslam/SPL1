#ifndef EXECUTION_H
#define EXECUTION_H
#include"operator.h"
vector<string>trimmedInstruction[1000];
vector<string>instruction;
void getInstruction(string pathName){
	int lineOfCode=0;
	ifstream file;
	file.open(pathName,ios::in);
	if(!file){
		cout<<"Error: Cannot open the given file!"<<endl;
		exit(0);
	}
	string tempStr;
	for(;;){
		if(!getline(file,tempStr)){
			break;
		}
		instruction.push_back(tempStr);
	}
	file.close();
}
void startExecution(string pathName){
    getInstruction(pathName);
	//cout<<"success1"<<endl;
    trim(instruction,trimmedInstruction,instruction.size());
	//cout<<"success2"<<endl;
    define(trimmedInstruction,instruction.size());
	//cout<<"success3"<<endl;
	getLabel(trimmedInstruction);
	executeInstruction(trimmedInstruction);
}
#endif