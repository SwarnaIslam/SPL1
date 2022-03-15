#ifndef OPERATOR_H
#define OPERATOR_H
#include"format.h"
#include"definition.h"
enum SysCode{
    printInt=1,
    scanInt=5,
    hexOfInt=34
};
void add(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    if(registers[hashOfRd].regName==""||registers[hashOfRd].regName=="$zero"||registers[hashOfRd].regName=="$at"){
        reportAndExit("Destination register must be from the valid registers(Note:$zero is not modifiable and $at is reserved for assembler)",instructionLine);
    }

    long long hashOfRs=getHashValue(command[2]);
    long long hashOfRt=getHashValue(command[3]);
    if(registers[hashOfRs].regName==""||registers[hashOfRs].regName=="$at"){
        reportAndExit("Source register must be from the valid registers(Note:$at is reserved for assembler)",instructionLine);
    }
    if(registers[hashOfRt].regName==""||registers[hashOfRt].regName=="$at"){
        reportAndExit("Source register must be from the valid registers(Note:$at is reserved for assembler)",instructionLine);
    }
    int32_t valRs=registers[hashOfRs].value;
    int32_t valRt=registers[hashOfRt].value;
    checkValidInteger(to_string((long long)valRs+(long long)valRt));
    //cout<<to_string((long long)valRs+(long long)valRt)<<endl;
    registers[hashOfRd].value=valRs+valRt;
}
void addu(){

}
void addi(vector<string>command,string instructionLine){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    long long hashOfRd=getHashValue(command[1]);
    if(registers[hashOfRd].regName==""||registers[hashOfRd].regName=="$zero"||registers[hashOfRd].regName=="$at"){
        reportAndExit("Destination register must be from the valid registers(Note:$zero is not modifiable and $at is reserved for assembler)",instructionLine);
    }

    long long hashOfRs=getHashValue(command[2]);
    string tempNumber=command[3];
    checkValidInteger(tempNumber);
    if(registers[hashOfRs].regName==""||registers[hashOfRs].regName=="$at"){
        reportAndExit("Source register must be from the valid registers(Note:$at is reserved for assembler)",instructionLine);
    }
    int32_t valRs=registers[hashOfRs].value;
    int32_t valImm=stol(tempNumber);
    checkValidInteger(to_string((long long)valRs+(long long)valImm));
    //cout<<to_string((long long)valRs+(long long)valImm)<<endl;
    registers[hashOfRd].value=valRs+valImm;
}
void li(vector<string>command,string instructionLine){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    checkValidInteger(command[2]);
    cout<<"Performing pseudo instruction..."<<endl;
    cout<<command[0]<<" "<<command[1]<<" "<<command[2]<<endl;
    cout<<endl;
    int32_t number=stoi(command[2]);
    int16_t lowerBits=number;
    int16_t higherBits=(number>>16);

    cout<<"Details of this operation:"<<endl;
    printf("lui $at %X\n",higherBits);
    printf("ori %s $at %X\n\n",command[1].c_str(),lowerBits);

    long long hashValue=getHashValue(command[1]);
    registers[hashValue].value=number;
}
void syscall(vector<string>command,string instructionLine){
    string input;
    long long hashValue=getHashValue("$v0");
    int32_t val=registers[hashValue].value;
    switch (val)
    {
    case printInt:
        hashValue=getHashValue("$a0");
        val=registers[hashValue].value;
        cout<<"Printing integer: ";
        cout<<val<<"\n\n";
        break;
    case scanInt:
        cout<<"Enter a integer: ";
        cin>>input;
        checkValidInteger(input);
        hashValue=getHashValue("$v0");
        registers[hashValue].value=stoi(input);
        cout<<"Stored input into $v0 register.\n\n";
        break;
    case hexOfInt:
        hashValue=getHashValue("$a0");
        val=registers[hashValue].value;
        cout<<"Printing integer in hexadecimal form: ";
        printf("%X\n\n",val);
        break;
    default:
        reportAndExit("Invalid system call",instructionLine);
        break;
    }
}
void move(vector<string>command,string instructionLine){
    long long hashOfRd=getHashValue(command[1]);
    long long hashOfRs=getHashValue(command[2]);
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    cout<<"Performing pseudo instruction..."<<endl;
    cout<<command[0]<<" "<<command[1]<<" "<<command[2]<<endl;
    cout<<endl;
    cout<<"Details of this operation:"<<endl;
    cout<<"add"<<" "<<command[1]<<" "<<"$zero"<<" "<<command[2]<<endl;
    registers[hashOfRd].value=registers[hashOfRs].value;
}
void perform(long long hashOfOp,vector<string>command,string instructionLine){
    if(hashOfOp==getHashValue("move")){
        move(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("li")){
        //cout<<"entered if li"<<endl;
        li(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("syscall")){
        syscall(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("add")){
        add(command,instructionLine);
    }
    else if(hashOfOp==getHashValue("addi")){
        addi(command,instructionLine);
    }
}
void executeInstruction(vector<string>trimmedInstruction[]){
    int textStart=getTextIndex();
    int dataStart=getDataIndex();
    int textEnd=0;
    string instructionLine="";
    map<string,int>labels=getTextLabel();
    if(dataStart<textStart){
        textEnd=getNumberOfInstruction();
    }
    else{
        if(dataStart==textStart+1){
            return;
        }
        else{
            textEnd=dataStart;
        }
    }
    for(int i=textStart+1;i<textEnd;i++){
        string tempOperator=trimmedInstruction[i][0];
        if(tempOperator==""){
            continue;
        }
        //cout<<tempOperator<<endl;
        vector<string>operators{"li","la","add","addi","mul","div","j","jal","bne","beq","move","syscall"};
        bool operatorFound=false;
        int instructionNum=0;
        long long hashOfTempOp=getHashValue(tempOperator);
        instructionLine=to_string(i+1);
        for(int j=0;j<operators.size();j++){
            long long hashOfOp=getHashValue(operators[j]);
            if(hashOfOp==hashOfTempOp){
                operatorFound=true;
                instructionNum=j;
                break;
            }
        }
        int labelFound=tempOperator.find(':');
        if(labelFound>0&&labelFound<tempOperator.size()){
            tempOperator=tempOperator.substr(0,labelFound);
        }
        if(operatorFound==false&&labels[tempOperator]==0){
            reportAndExit("Invalid operation in text section",instructionLine);
        }
        else{
            perform(hashOfTempOp,trimmedInstruction[i],to_string(i+1));
        }
        
    }
}
#endif