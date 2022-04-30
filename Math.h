#ifndef MATH_H
#define MATH_H
#include<iostream>
#include"debugger.h"
using namespace std;
void isNumber(string tempNumber){
    for(int32_t i=0;i<tempNumber.size();i++) //check that each character is a digit
	{
		if(tempNumber[i]=='-'&&i==0) //ignore minus sign
		{
			continue;
		}
		if(tempNumber[i]<'0'||tempNumber[i]>'9')
		{
            //cout<<tempNumber<<endl;
			reportAndExit("Specified value is not a number");
		}
	}
}
void checkValid32BitInteger(string tempNumber){
    //cout<<"Math: "<<tempNumber<<endl;
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
   // cout<<"Math: "<<tempNumber<<endl;
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
string twos_complement(string binVal){
    for(int i=0;i<32;i++)binVal[i]=(binVal[i]=='0')?'1':'0';
    char carry='1';
    for(int i=binVal.size()-1;i>=0;i--){
        if(carry=='1'&&binVal[i]=='1'){
            binVal[i]='0';
            carry='1';
        }
        else if(carry=='1'&&binVal[i]=='0'){
            binVal[i]='1';
            carry='0';
        }
    }
    //cout<<binVal<<endl;
    return binVal;
}
int32_t getNumber(string binResult){
    bool isNegative=false;
    if(binResult[0]=='1'){
        binResult=twos_complement(binResult);
        isNegative=true;
    }
    int p=1;
    int32_t number=0;
    for(int i=binResult.size()-1;i>=0;i--){
        if(binResult[i]=='1')number+=p;
        p*=2;
    }
    if(isNegative)number=number*(-1);
    //cout<<binResult<<"="<<binVal1<<"&"<<binVal2<<endl;
    return number;
}

string getBinaryValue(int32_t value){
    string binVal="";
    if(value==0)binVal="0"+binVal;
    if(value>0){
       // cout<<value<<" = ";
        while(value){
            if(value%2)binVal="1"+binVal;
            else binVal="0"+binVal;
            value/=2;
        }
        while(binVal.size()<32)binVal='0'+binVal;
    }
    else{
        //cout<<value<<" = ";
        value=value*(-1);
        while(value){
            if(value%2)binVal="1"+binVal;
            else binVal="0"+binVal;
            value/=2;
        }
        while(binVal.size()<32)binVal='0'+binVal;
        //cout<<"positive bin: "<<binVal<<endl;
        binVal=twos_complement(binVal);
    }
    //cout<<value<<" = "<<binVal<<endl;
    return binVal;
}
long long getUnsignedNumber(string value){
    string binResult=getBinaryValue(stoi(value));
    long long number=0;
    long long p=1;
    for(int i=binResult.size()-1;i>=0;i--){
        if(binResult[i]=='1')number+=p;
        p*=2;
    }
    return number;
}
int32_t userDefinedAnd(int32_t val1, int32_t val2){
    string binVal1=getBinaryValue(val1);
    string binVal2=getBinaryValue(val2);
    string binResult="";

    for(int i=0;i<32;i++){
        if(binVal1[i]=='0'||binVal2[i]=='0')binResult=binResult+'0';
        else binResult=binResult+'1';
    }
    int32_t number=getNumber(binResult);
    //cout<<binResult<<"="<<binVal1<<"&"<<binVal2<<endl;
    return number;
}
int32_t userDefinedOr(int32_t val1, int32_t val2){
    string binVal1=getBinaryValue(val1);
    string binVal2=getBinaryValue(val2);
    string binResult="";

    for(int i=0;i<32;i++){
        if(binVal1[i]=='1'||binVal2[i]=='1')binResult=binResult+'1';
        else binResult=binResult+'0';
    }
    int32_t number=getNumber(binResult);
    //cout<<binResult<<"="<<binVal1<<"&"<<binVal2<<endl;
    return number;
}
int32_t userDefinedNot(int32_t val){
    string binVal=getBinaryValue(val);
    string binResult=binVal;

    for(int i=0;i<32;i++){
        binVal[i]=(binVal[i]=='1')?'0':'1';
    }
    int32_t number=getNumber(binVal);
    //cout<<"notBin: "<<binVal<<endl;
    //cout<<"NotVal: "<<number<<endl;
    return number;
}
int32_t userDefinedNor(int32_t val1, int32_t val2){
    int32_t aOrb=userDefinedOr(val1,val2);

    int32_t number=userDefinedNot(number);
    //cout<<binResult<<"="<<binVal1<<"&"<<binVal2<<endl;
    return number;
}
int32_t userDefinedXor(int32_t val1, int32_t val2){
    int32_t aNotb=userDefinedAnd(val1,userDefinedNot(val2));
    int32_t bNota=userDefinedAnd(val2,userDefinedNot(val1));

    int32_t aXorb=userDefinedOr(aNotb,bNota);
    return aXorb;
}
#endif