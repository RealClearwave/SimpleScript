#include "SimpleScript.h"
#include <iostream>
#include <stdarg.h>
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif

void delay(double sec);
int delay0(std::string argv[]);
int print(std::string argv[]);
int println(std::string argv[]);
int prblnk(std::string argv[]);
int calisVari(std::string argv[]);
int decVari(std::string argv[]);
int addVari(std::string argv[]);
int subVari(std::string argv[]);
int mulVari(std::string argv[]);
int divVari(std::string argv[]);
int cinVari(std::string argv[]);
int comp(std::string argv[]);
int if_sel(std::string argv[]);
int go_to(std::string argv[]);
int crnd(std::string argv[]);
int cret(std::string argv[]);
int quit(std::string argv[]);
int decfunc(std::string argv[]);
int exefunc(std::string argv[]);
int crepeat(std::string argv[]);
int mimp(std::string argv[]);

int (*functbl[maxfunc])(std::string argv[]) = {
	print,println,delay0,calisVari,decVari,addVari,cinVari,
	comp,if_sel,go_to,prblnk,crnd,subVari,mulVari,
	divVari,cret,quit,decfunc,exefunc,crepeat,mimp
};

int execPro(int id, std::string argv[]){
	int ret = functbl[id](argv);
	return ret;
}

void delay(double sec){
	#ifdef _WIN32
		Sleep(sec*1000);
			#else
		sleep(sec);
	#endif
}

int delay0(std::string argv[]){
	double sec = std::stod(argv[0]);
	delay(sec);
	return 0;
}

int print(std::string argv[]){
	int i = -1; 
	while(argv[++i] != "") 
		std::cout<<argv[i];
		
	return 0;
}

int println(std::string argv[]){
	int i = -1; 
	while(argv[++i] != "") 
		std::cout<<argv[i];
	
	std::cout<<std::endl;
	return 0;
}

int prblnk(std::string argv[]){
	std::cout<<std::endl;
	return 0;
} 
int calisVari(std::string argv[]){
	return  (int)(isVari(argv[0]));
}

int decVari(std::string argv[]){ //
	variPush(argv[0],0);
	return 0;
}

int addVari(std::string argv[]){
	//std::cout<<argv[0]<<' '<<argv[1]<<std::endl;
	std::string x = argv[0],y = argv[1];
	int a,b;
	if (isVari(x))
		a = variFetch(x);
	else
		a = std::stoi(x);
		
	if (isVari(y))
		b = variFetch(y);
	else
		b = std::stoi(y);
		
	return a+b;
}

int subVari(std::string argv[]){
	//std::cout<<argv[0]<<' '<<argv[1]<<std::endl;
	std::string x = argv[0],y = argv[1];
	int a,b;
	if (isVari(x))
		a = variFetch(x);
	else
		a = std::stoi(x);
		
	if (isVari(y))
		b = variFetch(y);
	else
		b = std::stoi(y);
		
	return a-b;
}

int mulVari(std::string argv[]){
	std::string x = argv[0],y = argv[1];
	int a,b;
	if (isVari(x))
		a = variFetch(x);
	else
		a = std::stoi(x);
		
	if (isVari(y))
		b = variFetch(y);
	else
		b = std::stoi(y);
	
	//std::cout<<a<<' '<<b<<std::endl;
	return a*b;
}

int divVari(std::string argv[]){
	//std::cout<<argv[0]<<' '<<argv[1]<<std::endl;
	std::string x = argv[0],y = argv[1];
	int a,b;
	if (isVari(x))
		a = variFetch(x);
	else
		a = std::stoi(x);
		
	if (isVari(y))
		b = variFetch(y);
	else
		b = std::stoi(y);
		
	return a/b;
}

int getVari(std::string argv[]){
	return variFetch(argv[0]);
} 

int dspVari(std::string argv[]){
	std::cout<<variFetch(argv[0]);
}

int cinVari(std::string argv[]){
	int t;std::cin>>t;
	return t;
} 

int comp(std::string argv[]){
	int a,b;
	if (isVari(argv[1])) a = variFetch(argv[1]); else a = std::stoi(argv[1]);
	if (isVari(argv[2])) b = variFetch(argv[2]); else b = std::stoi(argv[2]);
	
	if (argv[0] == "=" && a == b) return true;
	if (argv[0] == "<" && a < b) return true;
	if (argv[0] == ">" && a > b) return true;
	
	return false;
} 

int if_sel(std::string argv[]){
	//std::cout<<"if Working.";
	int pos;bool workd = false;
	pos = argv[0].find("=");
	if (pos == -1) pos = argv[0].find("<");
	if (pos == -1) pos = argv[0].find(">");
	
	//std::cout<<pos<<' '<<argv[0][pos]<<std::endl;
	std::string rgv[] = {argv[0].substr(pos,1),argv[0].substr(0,pos), argv[0].substr(pos+1)};
	//std::cout<<rgv[0]<<' '<<rgv[1]<<' '<<rgv[2]<<std::endl;
	if (comp(rgv)){
		//std::cout<<"Working On Branch 1"<<std::endl;
		graDentify(argv[1]);
		workd = true;
	}else
		graDentify(argv[2]);
	
	return (int)(workd);
}

int go_to(std::string argv[]) {
	int line = std::stoi(argv[0]);
	fJump(line);
	return line;
}

int crnd(std::string argv[]){
	return rand();
}

int cret(std::string argv[]){
	fRet();
	return 0;
}

int quit(std::string argv[]){
	exit(0);
}

int decfunc(std::string argv[]){
	mDec(argv[0]);
}

int exefunc(std::string argv[]){
	return mExe(argv[0]);
}

int crepeat(std::string argv[]){ //3 args
	std::string var = argv[0];
	//std::cout<<"Begin:"<<var<<std::endl;
	int start = std::stoi(argv[1]),end = std::stoi(argv[2]),iorg = 0;
	if (!isVari(var)) variPush(var,start-1); else variMove(var,start-1);	
	
	while (variFetch(var) <= end){
		//std::cout<<variFetch(var)<<std::endl;
		variMove(var,variFetch(var)+1);
		if (variFetch(var) <= end) fExeuntil("}");
	}
	
	fign("}");
	variClear(var);
	//std::cout<<"Ends:"<<var<<' '<<variFetch(var)<<std::endl;
	return end - start + 1;
}

int mimp(std::string argv[]){
	ldmod(argv[0]);
	return 0;
}
