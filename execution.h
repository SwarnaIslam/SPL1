#ifndef EXECUTION_H
#define EXECUTION_H
#include"operator.h"
#include"spliter.h"
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
	defineNumberOfInstruction(instruction.size());
	defineRegisters();
	defineOperators();
	def::Memory.resize(100000000);
	trim(instruction);
	//cout<<"success2"<<endl;
    define();
	//cout<<"success3"<<endl;
	//getLabel();
	//cout<<"successfully got label"<<endl;
	//defineProgramCounter();
	//cout<<"Successful defining PC"<<endl;
	executeInstruction();
	//cout<<"SuccessFull execution"<<endl;
}
#endif