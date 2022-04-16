#ifndef FORMAT_H
#define FORMAT_H
#include"definition.h"
void isNumber(string tempNumber){
    for(int32_t i=0;i<tempNumber.size();i++) //check that each character is a digit
	{
		if(tempNumber[i]=='-'&&i==0) //ignore minus sign
		{
			continue;
		}
		if(tempNumber[i]<'0'||tempNumber[i]>'9')
		{
			reportAndExit("Specified value is not a number");
		}
	}
}
void checkValid32BitInteger(string tempNumber){
    isNumber(tempNumber);
    //cout<<tempNumber.substr(1)<<endl;
	if(tempNumber[0]!='-'&&stoi(tempNumber)>2147483647)
	{
		reportAndExit("Number out of range. Positive number shouble be less than 2147483648");
	}
	else if(tempNumber[0]=='-' && stoi(tempNumber)<-2147483648) //same check as above for negative integers
	{
		reportAndExit("Number out of range. Negative number should be greater than or equal to -2147483648");
	}
}
void checkValid16BitInteger(string tempNumber){
    isNumber(tempNumber);
	if(tempNumber[0]!='-'&&stoi(tempNumber)>32767)
	{
		reportAndExit("Number out of range. Positive number shouble be less than 32,767");
	}
	else if(tempNumber[0]=='-' && stoi(tempNumber)<-32768) //same check as above for negative integers
	{
		reportAndExit("Number out of range. Negative number should be greater than or equal to -65536");
	}
}
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
    //vector<string>tempOperations=getKeywords();
    //cout<<def::operators->searchBST(def::operators,token)<<endl;
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