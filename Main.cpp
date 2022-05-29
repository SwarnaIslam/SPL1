#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<map>
#include"headers.h"
using namespace std;
string pathName; 

int main()
{
	string str="......ASSEMULATION......";
	int space=(70-str.size())/2;
	cout<<"\n\n\n"<<endl;
	for(int i=0;i<space;i++){
		cout<<" ";
	}
	cout<<str<<"\n\n";
	cout<<"Enter path name of the MIPS assembly file: "<<endl;
	cin>>pathName;
	
	startExecution(pathName);
	cout<<"\nReport: Operation completed successfully\n\n"<<endl;
	return 0;
}
