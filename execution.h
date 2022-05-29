#ifndef EXECUTION_H
#define EXECUTION_H
#include"operator.h"
#include"spliter.h"
#include"format.h"
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
	define(instruction.size());
	trim(instruction);
	defineSectionIndex();
	executeInstruction();
		
}
#endif