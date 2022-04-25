#ifndef FORMAT_H
#define FORMAT_H
#include"definition.h"
#include"math.h"

void checkValidDestination(long long hashOfRd){
    if(registers[hashOfRd].regName==""||registers[hashOfRd].regName=="$zero"||registers[hashOfRd].regName=="$at"){
        reportAndExit("Destination register must be from the valid registers(Note:$zero is not modifiable and $at is reserved for assembler)");
    }
}

void checkValidSource(long long hashOfSrc){
    if(registers[hashOfSrc].regName==""||registers[hashOfSrc].regName=="$at"){
        reportAndExit("Source register must be from the valid registers(Note:$at is reserved for assembler)");
    }
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