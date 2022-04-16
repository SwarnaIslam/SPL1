#ifndef MEMORY_H
#define MEMORY_H
#include"debugger.h"
#include"format.h"
#include"Algorithm.h"
#define CAPACITY 10009

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

void findDataLabel(){
    
    def::dataTable=createDataHashTable(CAPACITY);

    for(int i=def::dataStart+1;i<def::dataEnd;i++){
        int labelFound=-1,j;
        int size=def::trimmedInstruction[i].size();
        bool labelFlag=false;
        if(def::trimmedInstruction[i][0]==""){
            continue;
        }
        for(j=0;j<size;j++){
            int tokenLength=def::trimmedInstruction[i][j].length();
            labelFound=def::trimmedInstruction[i][j].find(':');
            if(labelFound>-1&&labelFound<tokenLength){
                labelFlag=true;
                break;
            }
        }
        if(labelFlag==false){
            reportAndExit("Unknown operation in .data section",i);
        }
        string tempLabel="";
        string afterLabel=def::trimmedInstruction[i][j].substr(labelFound+1);
        if(j==0){
            tempLabel=def::trimmedInstruction[i][0].substr(0,labelFound);
        }
        else if(j==1){
            tempLabel=def::trimmedInstruction[i][0];
        }
        else{
            reportAndExit("Wrong format of label, seperate words must be connected with a underscore",i);
        }
        if(j==1&&labelFound!=0){
            reportAndExit("Wrong format of label, seperate words must be connected with a underscore",i);
        }
        else if(data_ht_search(def::dataTable,tempLabel)!=NULL){
            reportAndExit("Label "+tempLabel+" was defined before",i);
        }
        else if((afterLabel!=".word"||afterLabel!=".space")&&afterLabel!=""){
            reportAndExit("Invalid token after ':'",i);
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label",i);
        }
        
        if(afterLabel==".word"||afterLabel==".space"){
            if(afterLabel==".word"){
                int arraySize=def::trimmedInstruction[i].size()-j-1;
                int *tempArray=getNumber(def::trimmedInstruction[i], j+1, arraySize);
                //cout<<tempArray<<endl;
                
            }
            else{
                int arraySize=stoi(def::trimmedInstruction[i][j+1])/4;
                int* tempArray=(int*)calloc(arraySize, sizeof(int));
                
            }
        }
        else if(def::trimmedInstruction[i][j+1]==".word"||def::trimmedInstruction[i][j+1]==".space"){
            if(def::trimmedInstruction[i][j+1]==".word"){
                int arraySize=def::trimmedInstruction[i].size()-j-2;
                
                int *tempArray=getNumber(def::trimmedInstruction[i], j+2, arraySize);
                data_ht_insert(def::dataTable,tempLabel,arraySize*4,tempArray);
            }
            else{
                int arraySize=stoi(def::trimmedInstruction[i][j+2])/4;

                int* tempArray=(int*)calloc(arraySize, sizeof(int));
                data_ht_insert(def::dataTable,tempLabel,stoi(def::trimmedInstruction[i][j+2]),tempArray);
            }
        }
        else{
            reportAndExit("Expected directive after ':'",i);
        }
    }
    print_data_table(def::dataTable);
}
void findTextLabel(){

    BST<string,int>*occurred=NULL;
    
    for(int i=def::textStart+1;i<def::textEnd;i++){
    
        int labelFound=-1,j;
        int size=def::trimmedInstruction[i].size();
        bool labelFlag=false;
        if(def::trimmedInstruction[i][0]==""){
            continue;
        }
        for(j=0;j<size;j++){
            int tokenLength=def::trimmedInstruction[i][j].length();
            labelFound=def::trimmedInstruction[i][j].find(':');
            if(labelFound>-1&&labelFound<tokenLength){
                labelFlag=true;
                break;
            }
        }
        if(labelFlag==false){
            continue;
        }
        string tempLabel="";
        string afterLabel=def::trimmedInstruction[i][j].substr(labelFound+1);
        if(j+1<size){
            reportAndExit("No instruction is expected after label name",i);
        }
        if(j==0){
            tempLabel=def::trimmedInstruction[i][0].substr(0,labelFound);
        }
        else if(j==1){
            tempLabel=def::trimmedInstruction[i][0];
        }
        else{
            reportAndExit("Wrong format of label",i);
        }
        int prevIndex=occurred->searchBST(occurred,tempLabel);
        if(j==1&&labelFound!=0){
            reportAndExit("Wrong format of label",i);
        }
        else if(prevIndex!=0||data_ht_search(def::dataTable,tempLabel)!=NULL){
            reportAndExit("Label '"+tempLabel+"' was defined before",prevIndex);
        }
        else if(afterLabel!=""){
            reportAndExit("No instruction is expected after label name",i);
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label",i);
        }
        else{
            occurred=occurred->insertBST(tempLabel,i,occurred);
        }  
    }
    def::detectLabel=occurred;
    //print_text_table(def::textTable);
}
void getLabel(){

    findDataLabel();
    findTextLabel();

    // data_ht_insert(table,"sample",10,vector<int>(10));
    // data_ht_insert(table,"sample",10,vector<int>(20));
}
#endif