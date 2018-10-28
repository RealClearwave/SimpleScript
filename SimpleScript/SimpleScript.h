#pragma once
#include <string>
#include <map>

//calling procedures
const int  maxarg = 5001;
const int  maxfunc= 5001;
int execPro(int id, std::string argv[]);
//Grammar
void graInit();
bool isFunc(std::string x);
int isCal(std::string x);
std::string execl(std::string x);
bool exeable(std::string x);

struct line{
	#define _maxtr 3001
	int pts,argc;
	std::string va,func;
	std::string trunc[_maxtr],argv[_maxtr];
	std::string to_str;
	
	std::string str(){
		return to_str;
	}
	bool push(std::string x);
	std::string exec();
};

//Variable
void variPush(std::string x,int org = 0);
void variClear(std::string x);
void variMove(std::string x,int mv);
int variFetch(std::string x);
void variAdd(std::string x,std::string a);
void variMul(std::string x,std::string a);
void variDiv(std::string x,std::string a);
bool isVari(std::string x);
#define LESS 0
#define EQUAL 1
#define GREATER 2
int variCmp(std::string x,std::string y);

//Files
std::string fLoad(std::string fn);
bool fNext();
void fJump(int e);
void fExe(std::string fn);
void fRet();
int  mExe(std::string argv[]);
void mDec(std::string ms);
void fign(std::string fn);
void fExeuntil(std::string flg);
void ldmod(std::string fn);
bool isMod(std::string x);
bool fAddesp();
//Stylize
std::string SpaceErase(std::string line);
std::string calext(std::string ex);
