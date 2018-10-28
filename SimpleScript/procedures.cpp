#pragma once
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
int syscl(std::string argv[]);
int DeclReturn(std::string argv[]);
int els(std::string argv[]);
int (*functbl[maxfunc])(std::string argv[]) = {
	print,println,delay0,calisVari,decVari,addVari,cinVari,
	comp,if_sel,go_to,prblnk,crnd,subVari,mulVari,
	divVari,cret,quit,decfunc,exefunc,crepeat,mimp,
	syscl,DeclReturn,els
};

int execPro(int id, std::string argv[]){
	//std::cout<<"Exe "<<id<<' '<<std::endl;
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

int decVari(std::string argv[]){ 
	variPush(argv[0],0);
	return 0;
}

int addVari(std::string argv[]){
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
	
	return a*b;
}

int divVari(std::string argv[]){
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
	int pos;bool workd = false,sp2 = false;
	pos = argv[0].find("==");
	if (pos == -1) pos = argv[0].find("<");
	else sp2 = true;
	if (pos == -1) pos = argv[0].find(">");
	
	std::string ag1,ag2,ag3;
	ag1 = argv[0].substr(pos,1);
	ag2 = argv[0].substr(0,pos);
	ag3 = (sp2?argv[0].substr(pos+2):argv[0].substr(pos+1));
	if (isVari(ag1)) ag1 = std::to_string(variFetch(ag1)); 
	if (isVari(ag2)) ag2 = std::to_string(variFetch(ag2));
	if (isVari(ag3)) ag3 = std::to_string(variFetch(ag3));
	std::string rgv[] = {ag1,ag2,ag3};
//	std::cout<<comp(rgv)<<std::endl;
	
	if (comp(rgv)){
		cur.ExecuteScriptuntil("}");
		cur.IgnoreUntil("else");
		cur.IgnoreUntil("}");
		workd = true;
	}else{//std::cout<<"Gugu"<<std::endl; 
		cur.IgnoreUntil("else");
		cur.ExecuteScriptuntil("}");
		cur.IgnoreUntil("}");
	}
	
	return (int)(workd);
}

int els(std::string argv[]){
	std::cout<<"Gugu"<<std::endl;
}
int go_to(std::string argv[]) {
	int line = std::stoi(argv[0]);
	cur.JumpToLine(line);
	return line;
}

int crnd(std::string argv[]){
	return rand();
}

int cret(std::string argv[]){
	cur.DeclReturn();
	return 0;
}

int quit(std::string argv[]){
	exit(0);
}

int decfunc(std::string argv[]){
	cur.ModelDecode(argv[0]);
}

int exefunc(std::string argv[]){
	return cur.ModelExecute(argv);
}

int crepeat(std::string argv[]){ 
	std::string var = argv[0];
	int start,end;
	if (isVari(argv[1])) start = variFetch(argv[1]); else start = std::stoi(argv[1]);
	if (isVari(argv[2])) end   = variFetch(argv[2]); else end   = std::stoi(argv[2]);
	
	if (!isVari(var)) variPush(var,start); else variMove(var,start);	
	
	while (variFetch(var) <= end){
		cur.ExecuteScriptuntil("}");
		variMove(var,variFetch(var)+1);
	}
	
	cur.IgnoreUntil("}");
	variClear(var);
	return end - start + 1;
}

int mimp(std::string argv[]){
	cur.LoadModule(argv[0]);
	return 0;
}

int syscl(std::string argv[]){
	system(argv[0].c_str());
	return 0;
}

int DeclReturn(std::string argv[]){
	if (isVari(argv[0]))
		variMove("retv",variFetch(argv[0]));
	else
		variMove("retv",std::stoi(argv[0]));
	
	return 0;
}
