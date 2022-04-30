#ifndef SPLITER_H
#define SPLITER_H
#include<vector>
#include"definition.h"
#include"preprocess.h"
#include"debugger.h"
#include"memory.h"
using namespace std;
int len=0;
void commaRemove(char *untrimmedInstruction){
    int i=0;
    int f=-1;
    for(i=0;i<len;i++){
        if(untrimmedInstruction[i]==','){
            untrimmedInstruction[i]=' ';
        }
    }
}
void commentRemove(char unTrimmedInstruction[]){
    int f=-1;
    for(int i=0;i<len;i++){
        if(unTrimmedInstruction[i]=='#'){
            f=i;
            break;
        }
    }
    if(f<len&&f>=0){
        for(int i=f;i<len;i++){
            unTrimmedInstruction[i]=' ';
        }
    }
}
vector<string>split(char unTrimmedInstruction[],int s){
    vector<string>trimmedInstruction;
    len=s;
    commentRemove(unTrimmedInstruction);
    commaRemove(unTrimmedInstruction);
    int newLine=1;
    for(int i=0;i<len;i++){
        if(unTrimmedInstruction[i]!=' '&&unTrimmedInstruction[i]!='\0'&&unTrimmedInstruction[i]!='\n'&&unTrimmedInstruction[i]!='\t'&&unTrimmedInstruction[i]!='\r'){
            string temp="";
            newLine=0;
            for(int j=i;j<len;j++){
                if(unTrimmedInstruction[j]!=' '&&unTrimmedInstruction[j]!='\0'&&unTrimmedInstruction[j]!='\n'&&unTrimmedInstruction[j]!='\t'&&unTrimmedInstruction[j]!='\r'){
                    //cout<<temp<<endl;
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
void labelFind(vector<string>instruction){
    bool dataFound=false;
    bool textFound=false;
    bool tokenFound=false;
    def::dataTable=createDataHashTable(CAPACITY);
    BST<string,int>*occurred=NULL;
    for(int i=0;i<def::numberOfInstruction;i++){
		int InsLength=instruction[i].length()+1;
        if(InsLength==1)continue;

        string token=instruction[i].substr(0, InsLength-1);
        if(token!=".data"&&token!=".text"&&dataFound==false&&textFound==false){
            reportAndExit(".data or .text expected");
        }
        else if(token==".data"&&dataFound==true){
            reportAndExit("More than one .data is found");
        }
        else if(token==".text"&&textFound==true){
            reportAndExit("More than one .text is found");
        }
        else if(token==".data"&&dataFound==false){
            def::dataStart=i;
            dataFound=true;
        }
        else if(token==".text"&&textFound==false){
            def::textStart=i;
            textFound=true;
        }
	}
    for(int i=def::dataStart+1;i<def::numberOfInstruction;i++){
		int InsLength=instruction[i].length()+1;
        if(InsLength==1)continue;
        string token=instruction[i].substr(0, InsLength-1);

        if(token==".text")break;

        char tempIns[InsLength];
		for(int j=0;j<InsLength;j++){
			tempIns[j]=instruction[i][j];
		}
        vector<string>temp=split(tempIns,InsLength);
        findDataLabel(temp);
	}
    print_data_table(def::dataTable);
    for(int i=def::textStart+1;i<def::numberOfInstruction;i++){
		int InsLength=instruction[i].length()+1;
        int labelFound=-1;
        if(InsLength==1)continue;

        string token=instruction[i].substr(0, InsLength-1);
        labelFound=token.find(':');

        if(labelFound<0||labelFound>=InsLength-1)continue;
        if(token==".data")break;
        //cout<<labelFound<<endl;
        char tempIns[InsLength];
		for(int j=0;j<InsLength;j++){
			tempIns[j]=instruction[i][j];
		}
        vector<string>temp=split(tempIns,InsLength);
        findTextLabel(temp,i);
	}
    def::detectLabel->printBST(def::detectLabel);
}
void trim(vector<string>instruction){
    labelFind(instruction);
    def::textTable=createtextHashTable(CAPACITY);
	for(int i=def::textStart+1;i<def::numberOfInstruction;i++){
		int InsLength=instruction[i].length()+1;
        if(InsLength==1)continue;

        string token=instruction[i].substr(0, InsLength-1);
        int labelFound=token.find(':');
        if(labelFound>=0&&labelFound<=InsLength){
            token=token.substr(0,token.length()-1);
            token=removeWhiteSpace(token);
            //cout<<"Spliter: "<<token<<endl;
            text_ht_insert(def::textTable,token,def::trimLen-1,i);
            continue;
        }
		char tempIns[InsLength];
		for(int j=0;j<InsLength;j++){
			tempIns[j]=instruction[i][j];
		}
        //cout<<tempIns<<" "<<InsLength<<endl;
		vector<string>temp=split(tempIns,InsLength);
        //cout<<temp.size()<<endl;
        if(temp[0]!="")
            preprocess(temp);
	}
    print_text_table(def::textTable);
}
#endif