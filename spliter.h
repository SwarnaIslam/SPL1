#ifndef SPLITER_H
#define SPLITER_H
#include<vector>
#include"definition.h"
#include"preprocess.h"
#include"debugger.h"
#include"memory.h"
using namespace std;

void commaRemove(char *untrimmedInstruction, int len){
    int i=0;
    int f=-1;
    for(i=0;i<len;i++){
        if(untrimmedInstruction[i]==','){
            untrimmedInstruction[i]=' ';
        }
    }
}
void commentRemove(char unTrimmedInstruction[],int len){
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
vector<string>split(char unTrimmedInstruction[],int len){
    vector<string>trimmedInstruction;
    commentRemove(unTrimmedInstruction,len);
    commaRemove(unTrimmedInstruction,len);
    //cout<<unTrimmedInstruction<<endl;
    for(int i=0;i<len;i++){
            string temp="";
            if(unTrimmedInstruction[i]==' '||unTrimmedInstruction[i]=='\0'||unTrimmedInstruction[i]=='\n'||unTrimmedInstruction[i]=='\t'||unTrimmedInstruction[i]=='\r')continue;
            for(int j=i;j<len;j++){
                if(unTrimmedInstruction[j]!=' '&&unTrimmedInstruction[j]!='\0'&&unTrimmedInstruction[j]!='\n'&&unTrimmedInstruction[j]!='\t'&&unTrimmedInstruction[j]!='\r'){
                    //cout<<temp<<endl;
                    temp.push_back(unTrimmedInstruction[j]);
                    i++;
                }
                else{
                    trimmedInstruction.push_back(temp);
                    break;
                }
            }
            if(i==len&&temp!="")trimmedInstruction.push_back(temp);
    }
    
    return trimmedInstruction;
}
string stringStrip(string str){
    int i=0,j=str.length()-1;
    while((str[i]==' '||str[i]=='\t'||str[i]=='\n'||str[i]=='\r'||str[i]=='\0')&&i<=j){
        i++;
    }
    while((str[j]==' '||str[j]=='\t'||str[j]=='\n'||str[j]=='\r'||str[j]=='\0')&&j>=i){
        j--;
    }
    string tempStr="";
    for(int k=i;k<=j;k++){
        tempStr+=str[k];
    }
    return tempStr;
}
void getDataLabel(vector<string>instruction){
    for(int i=def::dataStart+1;i<def::numberOfInstruction;i++){
        string token=stringStrip(instruction[i]);
        int len=token.length();
        if(len==0)continue;
        if(token==".text")break;

        char tempIns[len+1]={};
		for(int j=0;j<len;j++){
			tempIns[j]=token[j];
		}
        
        vector<string>temp=split(tempIns,len);
    
        storeDataLabel(temp);
	}
    print_data_table(def::dataTable);
}
void getTextLabel(vector<string>instruction){
    for(int i=def::textStart+1;i<def::numberOfInstruction;i++){
		string token=stringStrip(instruction[i]);
        int len=token.length();
        if(len==0)continue;

        int labelFound=token.find(':');

        if(labelFound<0||labelFound>=len)continue;
        if(token==".data")break;
        //cout<<labelFound<<endl;
        char tempIns[len+1]={};
		for(int j=0;j<len;j++){
			tempIns[j]=token[j];
		}
        vector<string>temp=split(tempIns,len);
        storeTextLabel(temp,i);
	}
}
void labelFind(vector<string>instruction){
    bool dataFound=false;
    bool textFound=false;
    bool tokenFound=false;
    def::dataTable=createDataHashTable(CAPACITY);
    BST<string,int>*occurred=NULL;
    for(int i=0;i<def::numberOfInstruction;i++){
        string token=stringStrip(instruction[i]);
		int InsLength=token.length();
        if(InsLength==0)continue;

        //string token=instruction[i].substr(0, InsLength-1);
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
    getDataLabel(instruction);
    getTextLabel(instruction);
    
}
void trim(vector<string>instruction){
    labelFind(instruction);
    def::textTable=createtextHashTable(CAPACITY);
	for(int i=def::textStart+1;i<def::numberOfInstruction;i++){
		string token=stringStrip(instruction[i]);
		int InsLength=token.length();
        if(InsLength==0)continue;

        int colonIndex=token.find(':');
        if(colonIndex>=0&&colonIndex<InsLength){
            token=token.substr(0,colonIndex);
            text_ht_insert(def::textTable,token,def::trimLen,i+1);
            continue;
        }
		char tempIns[InsLength+1];
		for(int j=0;j<InsLength;j++){
			tempIns[j]=token[j];
		}
        
		vector<string>temp=split(tempIns,InsLength);
        preprocess(temp);
	}
    
    print_text_table(def::textTable);
}
#endif