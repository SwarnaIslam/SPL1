#ifndef MEMORY_H
#define MEMORY_H
#include"debugger.h"
#include"format.h"
#include"Algorithm.h"
#define CAPACITY 100000

int* getNumber(vector<string>dataLabel,int labelIndex, int arraySize){
    int i=0,j=0;
    int size=dataLabel.size();
    bool tokenFound=false;
    int *tempArray=(int*)calloc(arraySize,sizeof(int));
    for(i=labelIndex;i<size;i++){
        checkValid32BitInteger(dataLabel[i]);
        tempArray[j++]=stoi(dataLabel[i]);
    }
    return tempArray;
}
int endIndex(int start1, int start2, int instructionNumber){
    int end=-1;
    if(start1>start2){
        end=instructionNumber;
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
void findDataLabel(vector<string>trimmedInstruction[],int dataStart, int textStart){
    int instructionNumber=getNumberOfInstruction();
    int dataEnd=endIndex(dataStart, textStart, instructionNumber);;
    string instructionLine="";
    BST<string,int>*hasOccurred=NULL;
    data_hashTable* table=create_dataTable(CAPACITY);


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
            reportAndExit("Unknown operation in .data section",instructionLine);
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
            reportAndExit("Wrong format of label, seperate words must be connected with a underscore",instructionLine);
        }
        if(j==1&&labelFound!=0){
            reportAndExit("Wrong format of label, seperate words must be connected with a underscore",instructionLine);
        }
        else if(hasOccurred->searchBST(hasOccurred,tempLabel)>0){
            reportAndExit("Label "+tempLabel+" was defined before",to_string(hasOccurred->searchBST(hasOccurred,tempLabel)));
        }
        else if((afterLabel!=".word"||afterLabel!=".space")&&afterLabel!=""){
            reportAndExit("Invalid token after ':'",instructionLine);
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label",instructionLine);
        }
        else{
            hasOccurred=hasOccurred->insertBST(tempLabel,i+1,hasOccurred);
            setDataLabel(tempLabel,i+1);
        }
        if(afterLabel==".word"||afterLabel==".space"){
            if(afterLabel==".word"){
                int arraySize=trimmedInstruction[i].size()-j-1;
                int *tempArray=getNumber(trimmedInstruction[i], j+1, arraySize);
                cout<<tempArray<<endl;
                
            }
            else{
                int arraySize=stoi(trimmedInstruction[i][j+1])/4;
                int* tempArray=(int*)calloc(arraySize, sizeof(int));
                
            }
        }
        else if(trimmedInstruction[i][j+1]==".word"||trimmedInstruction[i][j+1]==".space"){
            if(trimmedInstruction[i][j+1]==".word"){
                int arraySize=trimmedInstruction[i].size()-j-2;
                
                int *tempArray=getNumber(trimmedInstruction[i], j+2, arraySize);
                data_ht_insert(table,tempLabel,arraySize*4,tempArray);
            }
            else{
                int arraySize=stoi(trimmedInstruction[i][j+2])/4;

                int* tempArray=(int*)calloc(arraySize, sizeof(int));
                data_ht_insert(table,tempLabel,stoi(trimmedInstruction[i][j+2]),tempArray);
            }
        }
        else{
            reportAndExit("Expected directive after ':'",instructionLine);
        }
    }
    print_data_table(table);
}
void findTextLabel(vector<string>trimmedInstruction[],int dataStart, int textStart){
    int instructionNumber=getNumberOfInstruction();
    int textEnd=0;
    string instructionLine="";
    BST<string,int>*hasOccurred=getDataLabel();
    textEnd=endIndex(textStart, dataStart, instructionNumber);
    
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
        else if(hasOccurred->searchBST(hasOccurred,tempLabel)>0){
            reportAndExit("Label '"+tempLabel+"' was defined before",to_string(hasOccurred->searchBST(hasOccurred,tempLabel)));
        }
        else if(afterLabel!=""){
            reportAndExit("No instruction is expected after label name",instructionLine);
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label",instructionLine);
        }
        else{
            hasOccurred->insertBST(tempLabel,i+1,hasOccurred);
            setTextLabel(tempLabel,i+1);
        }  
    }
}
void getLabel(vector<string>trimmedInstruction[]){
    int dataStart=getDataIndex();
    int textStart=getTextIndex();
    findDataLabel(trimmedInstruction,dataStart,textStart);
    findTextLabel(trimmedInstruction,dataStart,textStart);

    // data_ht_insert(table,"sample",10,vector<int>(10));
    // data_ht_insert(table,"sample",10,vector<int>(20));
}
#endif