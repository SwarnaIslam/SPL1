#ifndef MEMORY_H
#define MEMORY_H
#include"debugger.h"
#include"format.h"
#include"Algorithm.h"
#define CAPACITY 10009
int memLen=0;
int* getNumber(vector<string>dataLabel,int labelIndex, int arraySize){
    int i=0,j=0;
    int size=dataLabel.size();
    bool tokenFound=false;
    int *tempArray=(int*)calloc(arraySize,sizeof(int));
    for(i=labelIndex;i<size;i++){
        //cout<<"memory: "<<dataLabel[i]<<endl;
        checkValid32BitInteger(dataLabel[i]);
        tempArray[j++]=stoi(dataLabel[i]);
    }
    return tempArray;
}
void pushStaticData(int *array, int arraySize){
    for(int i=0;i<arraySize;i++){
        def::Memory[memLen++]=array[i];
        //cout<<array[i]<<endl;
    }
    //cout<<def::Memory.size()<<endl;
}
void storeDataLabel(vector<string>command){
        //cout<<command[0]<<endl;
        int colonIndex=-1,j=0;
        int size=command.size();
        bool labelFlag=false;
        for(j=0;j<size;j++){
            int tokenLength=command[j].length();
            colonIndex=command[j].find(':');
            if(colonIndex>-1&&colonIndex<tokenLength){
                labelFlag=true;
                break;
            }
        }
        if(labelFlag==false){
            reportAndExit("Unknown operation in .data section");
        }
        string tempLabel="";
        string afterLabel=command[j].substr(colonIndex+1);
        if(j==0){
            tempLabel=command[0].substr(0,colonIndex);
        }
        else if(j==1){
            tempLabel=command[0];
        }
        else{
            reportAndExit("Wrong format of label, seperate words must be connected with a underscore");
        }
        if(j==1&&colonIndex!=0){
            reportAndExit("Wrong format of label, seperate words must be connected with a underscore");
        }
        else if(data_ht_search(def::dataTable,tempLabel)!=NULL){
            reportAndExit("Label "+tempLabel+" was defined before");
        }
        else if((afterLabel!=".word"||afterLabel!=".space")&&afterLabel!=""){
            reportAndExit("Invalid token after ':'");
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label");
        }
        
        if(afterLabel==".word"||afterLabel==".space"){
            if(afterLabel==".word"){
                int arraySize=command.size()-j-1;

                int *tempArray=getNumber(command, j+1, arraySize);
                pushStaticData(tempArray,arraySize);
                data_ht_insert(def::dataTable,tempLabel,arraySize*4);
                
            }
            else{
                int arraySize=ceil(stod(command[j+1])/4.0);

                int* tempArray=(int*)calloc(arraySize, sizeof(int));
                pushStaticData(tempArray,arraySize);
                data_ht_insert(def::dataTable,tempLabel,arraySize*4);
                
            }
        }
        else if(command[j+1]==".word"||command[j+1]==".space"){
            if(command[j+1]==".word"){
                int arraySize=command.size()-j-2;
                
                int *tempArray=getNumber(command, j+2, arraySize);
                pushStaticData(tempArray,arraySize);
                data_ht_insert(def::dataTable,tempLabel,arraySize*4);
            }
            else{
                int arraySize=ceil(stod(command[j+2])/4.0);

                int* tempArray=(int*)calloc(arraySize, sizeof(int));
                pushStaticData(tempArray,arraySize);
                data_ht_insert(def::dataTable,tempLabel,arraySize*4);
            }
        }
        else{
            reportAndExit("Expected directive after ':'");
        }
}
void storeTextLabel(vector<string>command,int currIndex){
        
        int labelFound=-1,j;
        int size=command.size();
        bool labelFlag=false;
        for(j=0;j<size;j++){
            int tokenLength=command[j].length();
            labelFound=command[j].find(':');
            if(labelFound>-1&&labelFound<tokenLength){
                labelFlag=true;
                break;
            }
        }
        string tempLabel="";
        string afterLabel=command[j].substr(labelFound+1);
        if(j+1<size){
            reportAndExit("No instruction is expected after label name");
        }
        if(j==0){
            tempLabel=command[0].substr(0,labelFound);
        }
        else if(j==1){
            tempLabel=command[0];
        }
        else{
            reportAndExit("Wrong format of label");
        }
        int prevIndex=def::detectLabel->searchBST(def::detectLabel,tempLabel);
        if(j==1&&labelFound!=0){
            reportAndExit("Wrong format of label");
        }
        else if(prevIndex!=0||data_ht_search(def::dataTable,tempLabel)!=NULL){
            reportAndExit("Label '"+tempLabel+"' was defined before",prevIndex);
        }
        else if(afterLabel!=""){
            reportAndExit("No instruction is expected after label name");
        }
        else if(!isValidLabel(tempLabel)){
            reportAndExit("Wrong format of label");
        }
        else{
            //cout<<"Creating label"<<endl;
            def::detectLabel=def::detectLabel->insertBST(tempLabel,currIndex+1,def::detectLabel);
        }
}
#endif