#ifndef MEMORY_H
#define MEMORY_H
#include"debugger.h"
#include"format.h"
string getNumber(vector<string>dataLabel,int labelIndex,string instructionLine){
    int i=0;
    int size=dataLabel.size();
    bool tokenFound=false;
    for(i=labelIndex;i<size;i++){
        if(tokenFound==true){
            reportAndExit("Found more than one token after .word",instructionLine);
        }
        tokenFound=true;
    }
    return dataLabel[size-1];
}
void findDataLabel(vector<string>trimmedInstruction[],int dataStart, int textStart){
    int instructionNumber=getNumberOfInstruction();
    int dataEnd=0;
    string instructionLine="";
    map<string,int>hasOccurred;
    if(dataStart>textStart){
        dataEnd=instructionNumber;
    }
    else{
        if(dataStart+1==textStart){
            return;
        }
        else{
            dataEnd=textStart;
        }
    }
    for(int i=dataStart+1;i<dataEnd;i++){
        instructionLine=to_string(i+1);
        int labelFound=-1,j;
        int size=trimmedInstruction[i].size();
        bool labelFlag=false;
        if(trimmedInstruction[i][0]==""){
            continue;
        }
        for(j=0;j<size;j++){
            int tokenLength=trimmedInstruction[i][j].length();
            labelFound=trimmedInstruction[i][j].find(':');
            if(labelFound>-1&&labelFound<tokenLength){
                labelFlag=true;
                break;
            }
        }
        if(labelFlag==false){
            reportAndExit("Unknown operation",instructionLine);
        }
        string tempLabel="";
        string afterLabel=trimmedInstruction[i][j].substr(labelFound+1);
        if(j==0){
            tempLabel=trimmedInstruction[i][0].substr(0,labelFound);
        }
        else if(j==1){
            tempLabel=trimmedInstruction[i][0];
        }
        else{
            reportAndExit("Wrong format of label",instructionLine);
        }
        if(j==1&&labelFound!=0){
            reportAndExit("Wrong format of label",instructionLine);
        }
        else if(hasOccurred[tempLabel]>0){
            reportAndExit("Label "+tempLabel+" was defined before",to_string(hasOccurred[tempLabel]));
        }
        else if(afterLabel!=".word"&&afterLabel!=""){
            reportAndExit("Invalid token after ':'",instructionLine);
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label",instructionLine);
        }
        else{
            hasOccurred[tempLabel]=i+1;
            setDataLabel(tempLabel,i+1);
        }
        string tempNumber="";
        if(afterLabel==".word"){
            tempNumber=getNumber(trimmedInstruction[i],j+1,instructionLine);
        }
        else if(trimmedInstruction[i][j+1]==".word"){
            tempNumber=getNumber(trimmedInstruction[i],j+2,instructionLine);
        }
        else{
            reportAndExit("Expected .word after ':'",instructionLine);
        }
        //cout<<tempNumber<<endl;
        checkValidInteger(tempNumber);
    }
}
void findTextLabel(vector<string>trimmedInstruction[],int dataStart, int textStart){
    int instructionNumber=getNumberOfInstruction();
    int textEnd=0;
    string instructionLine="";
    map<string,int>hasOccurred=getDataLabel();
    //cout<<dataStart<<" "<<endl;
    if(dataStart<textStart){
        textEnd=instructionNumber;
        //cout<<instructionNumber<<" "<<getNumberOfInstruction()<<endl;
    }
    else{
        if(dataStart==textStart+1){
            return;
        }
        else{
            textEnd=dataStart;
        }
    }
    for(int i=textStart+1;i<textEnd;i++){
        //cout<<"Entered loop"<<endl;
        instructionLine=to_string(i+1);
        int labelFound=-1,j;
        int size=trimmedInstruction[i].size();
        bool labelFlag=false;
        if(trimmedInstruction[i][0]==""){
            continue;
        }
        for(j=0;j<size;j++){
            int tokenLength=trimmedInstruction[i][j].length();
            labelFound=trimmedInstruction[i][j].find(':');
            if(labelFound>-1&&labelFound<tokenLength){
                labelFlag=true;
                break;
            }
        }
        if(labelFlag==false){
            continue;
        }
        string tempLabel="";
        string afterLabel=trimmedInstruction[i][j].substr(labelFound+1);
        if(j+1<size){
            reportAndExit("No instruction is expected after label name",instructionLine);
        }
        if(j==0){
            tempLabel=trimmedInstruction[i][0].substr(0,labelFound);
        }
        else if(j==1){
            tempLabel=trimmedInstruction[i][0];
        }
        else{
            reportAndExit("Wrong format of label",instructionLine);
        }
        //cout<<tempLabel<<" "<<hasOccurred[tempLabel]<<endl;
        if(j==1&&labelFound!=0){
            reportAndExit("Wrong format of label",instructionLine);
        }
        else if(hasOccurred[tempLabel]>0){
            reportAndExit("Label '"+tempLabel+"' was defined before",to_string(hasOccurred[tempLabel]));
        }
        else if(afterLabel!=""){
            reportAndExit("No instruction is expected after label name",instructionLine);
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label",instructionLine);
        }
        else{
            hasOccurred[tempLabel]=i+1;
            setTextLabel(tempLabel,i+1);
        }  
    }
}
void getLabel(vector<string>trimmedInstruction[]){
    int dataStart=getDataIndex();
    int textStart=getTextIndex();
    findDataLabel(trimmedInstruction,dataStart,textStart);
    findTextLabel(trimmedInstruction,dataStart,textStart);
}
#endif