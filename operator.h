#ifndef OPERATOR_H
#define OPERATOR_H
void add(){

}
void addu(){

}
void addi(){

}
void move(vector<string>command,string instructionLine){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section",instructionLine);
    }
    cout<<"Performing pseudo instruction..."<<endl;
    cout<<command[0]<<" "<<command[1]<<" "<<command[2]<<endl;
    cout<<endl;
    cout<<"Details of this operation:"<<endl;
    cout<<"add"<<" "<<command[1]<<" "<<"$zero"<<" "<<command[2]<<endl;
}
void perform(int instructionNum,vector<string>command,string instructionLine){
    switch (instructionNum)
    {
    case 10:
        move(command,instructionLine);
        break;
    
    default:
        break;
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
        vector<string>operators{"li","la","add","addi","mul","div","j","jal","bne","beq","move","syscall"};
        bool operatorFound=false;
        int instructionNum=0;
        instructionLine=to_string(i+1);
        for(int j=0;j<operators.size();j++){
            if(operators[j]==tempOperator){
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
            perform(instructionNum,trimmedInstruction[i],to_string(i+1));
        }
    }
}
#endif