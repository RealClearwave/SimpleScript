#pragma once
#include <string>
#include <vector>
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
struct File{
	#define max_lines 10001 // Being Reduced.
	#define max_mods 301
	std::vector<line> ln;
	int esp;
	int rtl[max_lines],rtc;
	std::map<std::string,int> fun2ln;
	
	void TruncFile(std::string x); 
	std::string LoadFile(std::string fn);
	bool ExecuteNextLine();
	void JumpToLine(int e);
	void ExecuteScript(std::string fn);
	void DeclReturn();
	int  ModelExecute(std::string argv[]);
	void ModelDecode(std::string ms);
	void IgnoreUntil(std::string fn);
	void ExecuteScriptuntil(std::string flg);
	void LoadModule(std::string fn);
	bool isModel(std::string x);
	bool SkipCurrentLine();
};

extern File cur; 

//Stylize
std::string SpaceErase(std::string line);
std::string CalculationExtend(std::string ex);
