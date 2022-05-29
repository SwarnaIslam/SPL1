#ifndef ITYPEPREPROCESSOR_H
#define ITYPEPREPROCESSOR_H
#include<iostream>
#include"definition.h"
#include"format.h"
#include "Math.h"
#include"psedo.h"
using namespace std;
void addiPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    checkValidSource(command[2]);

    string tempNumber=command[3];
    checkValid16BitInteger(tempNumber);

    def::trimmedInstruction[def::trimLen++]=command;
}
void addiuPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    checkValidSource(command[2]);

    checkValid16BitInteger(command[3]);

    def::trimmedInstruction[def::trimLen++]=command;
}
void liPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    checkValid32BitInteger(command[2]);
    
    extension(command);
    
}
void andiPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    checkValidSource(command[2]);

    checkValid16BitInteger(command[3]);
    def::trimmedInstruction[def::trimLen++]=command;
}
void oriPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    
    checkValidDestination(command[1]);
    checkValidSource(command[2]);
    checkValid32BitInteger(command[3]);

    extension(command);
}
void luiPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    checkValid16BitInteger(command[2]);
    
    def::trimmedInstruction[def::trimLen++]=command;
}
void sltiPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidDestination(command[1]);
    checkValidSource(command[2]);
    checkValid16BitInteger(command[3]);

    def::trimmedInstruction[def::trimLen++]=command;
}
void beqPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidSource(command[1]);
    checkValidSource(command[2]);
    if(!isLabel(command[3])){
        reportAndExit("Label not found");
    }
    def::trimmedInstruction[def::trimLen++]=command;
}
void bnePre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    checkValidSource(command[1]);
    checkValidSource(command[2]);
    if(!isLabel(command[3])){
        reportAndExit("Label not found");
    }

    def::trimmedInstruction[def::trimLen++]=command;
}
void bltPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidSource(command[1]);
    checkValidSource(command[2]);
    if(!isLabel(command[3])){
        reportAndExit("Label not found");
    }

    extension(command);
}
void bgtPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidSource(command[1]);
    checkValidSource(command[2]);
    if(!isLabel(command[3])){
        reportAndExit("Label not found");
    }

    extension(command);
}
void lwPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    int openingFound=command[2].find('(');
    int len=command[2].length();
    if(openingFound<len&&openingFound>=0){
        int closingFound=command[2].find(')');
        if(closingFound>=len||closingFound<0){
            reportAndExit("Couldn't found closing curly brace");
        }

        string tempRegister=command[2].substr(openingFound+1,closingFound-openingFound-1);
        checkValidSource(tempRegister);

        string temp=command[2].substr(0, openingFound);

        dataHashTableItem* item=data_ht_search(def::dataTable,temp);
        if(item==NULL){
            isNumber(temp);
        }
    }
    else{
        dataHashTableItem* item=data_ht_search(def::dataTable,command[2]);
        if(item==NULL){
            reportAndExit("Expected label");
        }
    }
    def::trimmedInstruction[def::trimLen++]=command;
}
void swPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValidSource(command[1]);
    int openingFound=command[2].find('(');
    int len=command[2].length();
    if(openingFound<len&&openingFound>=0){
        int closingFound=command[2].find(')');
        if(closingFound>=len||closingFound<0){
            reportAndExit("Couldn't found closing curly brace");
        }

        string tempRegister=command[2].substr(openingFound+1,closingFound-openingFound-1);
        checkValidDestination(tempRegister);

        string temp=command[2].substr(0, openingFound);

        dataHashTableItem* item=data_ht_search(def::dataTable,temp);
        if(item==NULL){
            isNumber(temp);
        }
    }
    else{
        dataHashTableItem* item=data_ht_search(def::dataTable,command[2]);
        if(item==NULL){
            reportAndExit("Expected label");
        }
    }
    def::trimmedInstruction[def::trimLen++]=command;
}
void laPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    dataHashTableItem* item=data_ht_search(def::dataTable,command[2]);

    if(item==NULL){
        reportAndExit("Expected label");
    }
    checkValidDestination(command[1]);
    def::trimmedInstruction[def::trimLen++]=command;
}

#endif