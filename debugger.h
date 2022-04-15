#ifndef DEBUGGER_H
#define DEBUGGER_H
#include<string>
#include"definition.h"
using namespace std;
void reportAndExit(string errorMessage){
    cout<<"Error: "<<errorMessage<<" at line "<<def::PC+1<<endl;
    exit(1);
}
void warning(string errorMessage, string instructionLine=""){
    cout<<"Warning: "<<errorMessage<<"at line "<<instructionLine<<endl;
}
#endif