#ifndef FORMAT_H
#define FORMAT_H
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
	if(tempNumber[0]!='-'&&tempNumber>"2147483647"&&tempNumber.length()>=10)
	{
		reportAndExit("Number out of range. Positive number shouble be less than 2147483648");
	}
	else if(tempNumber[0]=='-' && tempNumber.substr(1)>"2147483648"&&tempNumber.substr(1).length()>=10) //same check as above for negative integers
	{
		reportAndExit("Number out of range. Negative number should be greater than or equal to -2147483648");
	}
}
void checkValid16BitInteger(string tempNumber){
    isNumber(tempNumber);
	if(tempNumber[0]!='-'&&tempNumber>"65535"&&tempNumber.length()>=5)
	{
		reportAndExit("Number out of range. Positive number shouble be less than 65536");
	}
	else if(tempNumber[0]=='-' && tempNumber.substr(1)>"65536"&&tempNumber.substr(1).length()>=5) //same check as above for negative integers
	{
		reportAndExit("Number out of range. Negative number should be greater than or equal to -65536");
	}
}
void checkValidDestination(long long hashOfRd,string instructionLine){
    if(registers[hashOfRd].regName==""||registers[hashOfRd].regName=="$zero"||registers[hashOfRd].regName=="$at"){
        reportAndExit("Destination register must be from the valid registers(Note:$zero is not modifiable and $at is reserved for assembler)",instructionLine);
    }
}

void checkValidSource(long long hashOfSrc,string instructionLine){
    if(registers[hashOfSrc].regName==""||registers[hashOfSrc].regName=="$at"){
        reportAndExit("Source register must be from the valid registers(Note:$at is reserved for assembler)",instructionLine);
    }
}
bool isValidKeyword(string token){
    vector<string>tempOperations=getKeywords();
    for(int i=0;i<tempOperations.size();i++){
        if(tempOperations[i]==token){
            return true;
        }
    }
    return false;
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