#ifndef FORMAT_H
#define FORMAT_H

void checkValidInteger(string tempNumber){
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
	if(tempNumber[0]!='-'&&(tempNumber.size()>10||(tempNumber.size()==10 &&tempNumber>"2147483647")))
	{
		reportAndExit("Number out of range. Positive number shouble be less than 2147483648");
	}
	else if(tempNumber[0]=='-' && (tempNumber.size()>11||(tempNumber.size()==11 && tempNumber>"-2147483648"))) //same check as above for negative integers
	{
		reportAndExit("Number out of range. Negative number should be greater than or equal to -2147483648");
	}
}
bool isValidOperator(string tempOp){
    
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