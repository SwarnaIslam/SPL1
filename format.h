#ifndef FORMAT_H
#define FORMAT_H
#include<sstream>
#include"definition.h"
#include"math.h"
bool isLabel(string tempLabel){
    int labelIndex=tempLabel.find(':');
    if(labelIndex>0&&labelIndex<tempLabel.size()){
        tempLabel=tempLabel.substr(0,labelIndex);
    }
    bool labelFound=def::detectLabel->searchBST(def::detectLabel, tempLabel);
    if(labelFound){
        return true;
    }
    else{
        return false;
    }
}
string removeWhiteSpace(string token){
    string temp="";
    for(int i=0;token[i]!='\0';i++){
        if(token[i]!=' '&&token[i]!='\t'&&token[i]!='\0'&&token[i]!='\r'&&token[i]!='\n'){
            //cout<<token[i]<<endl;
            temp.push_back(token[i]);
        }
    } 
    //cout<<"Format: "<<temp<<endl;
    return temp;   
}
void checkRegister(string tempReg){
    vector<string>registers{"$zero","$at","$v0","$v1","$a0","$a1","$a2","$a3","$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$s0","$s1","$s2","$s3","$s4","$s5","$s6","$s7","$t8","$t9","$k0","$k1","$gp","$sp","$fp","$ra"};

    for(string reg:registers){
        if(tempReg==reg){
            return;
        }
    }
    reportAndExit("Expected register");
}
void checkValidDestination(string regName){
    if(regName==""||regName=="$zero"){
        reportAndExit("Destination register must be from the valid registers(Note:$zero is not modifiable and $at is reserved for assembler)");
    }
}

void checkValidSource(string regName){
    if(regName==""||regName=="$at"){
        reportAndExit("Source register must be from the valid registers(Note:$at is reserved for assembler)");
    }
}
void checkValidReg(string Rd, string Rs,string Rt){
    checkValidDestination(Rd);
    checkValidSource(Rs);
    checkValidSource(Rt);
}
bool isValidKeyword(string token){
    if(def::operators->searchBST(def::operators,token)==0){
        return false;
    }
    return true;
}
bool isValidLabel(string token){
    if(isValidKeyword(token))return false;
    for(int i=0;i<token.length();i++){
        if(i==0){
            if(token[0]<65||(token[0]>90&&token[0]<97)||token[0]>121){
                return false;
            }
        }
        else{
            if((token[i]>47&&token[i]<57)||(token[i]>64&&token[i]<91)||(token[i]>96&&token[i]<123)){
                return true;
            }
        }
    }
    return true;
}

#endif