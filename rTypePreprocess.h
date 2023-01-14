#ifndef RTYPEPREPROCESS_H
#define RTYPEPREPROCESS_H
#include<iostream>
#include"definition.h"
#include"format.h"
#include"Math.h"
#include"psedo.h"
using namespace std;

void syscallPre(vector<string>command){
    def::trimmedInstruction[def::trimLen++]=command;
}
void generalPurposePre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    
    checkValidReg(command[1],command[2],command[3]);
    def::trimmedInstruction[def::trimLen++]=command;

}
void movePre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    checkValidSource(command[2]);
    extension(command);
}

void multPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }

    checkValidSource(command[1]);
    checkValidSource(command[2]);
    def::trimmedInstruction[def::trimLen++]=command;
}
void divPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }

    checkValidSource(command[1]);
    checkValidSource(command[2]);
    def::trimmedInstruction[def::trimLen++]=command;
}

void mfloPre(vector<string>command){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    def::trimmedInstruction[def::trimLen++]=command;
}
void mfhiPre(vector<string>command){
    if(command.size()!=2){
        reportAndExit("Invalid operation in text section");
    }
    checkValidDestination(command[1]);
    def::trimmedInstruction[def::trimLen++]=command;
}
void sllPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidDestination(command[1]);
    checkValidSource(command[2]);

    int shift_amount=stoi(command[3]);

    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }     
    def::trimmedInstruction[def::trimLen++]=command;                                                                                                                                                                                                                                                                                                                     
}
void sgtPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }
    checkValidReg(command[1],command[2],command[3]);
    sgtExtension(command);
}
void srlPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidDestination(command[1]);
    checkValidSource(command[2]);

    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }  
    def::trimmedInstruction[def::trimLen++]=command;                                                                                                                                                                                                                                                                                                                     
}

void sraPre(vector<string>command){
    if(command.size()!=4){
        reportAndExit("Invalid operation in text section");
    }

    checkValidDestination(command[1]);
    checkValidSource(command[2]);

    int shift_amount=stoi(command[3]);
    if(shift_amount>31||shift_amount<0){
        reportAndExit("Shift amount must be between 0 to 31");
    }
    def::trimmedInstruction[def::trimLen++]=command;                                                                                                                                                                                                                                                                                                                          
}

void NotPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }

    checkValidDestination(command[1]);
    checkValidSource(command[2]);
    def::trimmedInstruction[def::trimLen++]=command;
}

void absPre(vector<string>command){
    if(command.size()!=3){
        reportAndExit("Invalid operation in text section");
    }

    checkValidDestination(command[1]);
    checkValidSource(command[2]);
    
    extension(command);
}

#endif