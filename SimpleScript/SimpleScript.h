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
	bool isret;
	bool good;
	std::string str(){
		return to_str;
	}
	bool push(std::string x);
	bool contain(std::string x);
	std::string exec();
};

//Variable
struct Variable{
	#define LESS 0
	#define EQUAL 1
	#define GREATER 2
	static int Cmp(std::string x,std::string y);
	static void Push(std::string x,int org = 0);
	static void Clear(std::string x);
	static void Move(std::string x,int mv);
	static int Fetch(std::string x);
	static bool isVari(std::string x);
	static std::string arrext(std::string x);
};



//Files
struct File{
	#define max_lines 10001 // Being Reduced.
	#define max_mods 301
	
	static void TruncFile(std::string x); 
	static std::string LoadFile(std::string fn);
	static bool ExecuteNextLine();
	static void JumpToLine(int e);
	static void ExecuteScript(std::string fn);
	static void DeclReturn();
	static int  ModelExecute(std::string argv[]);
	static void ModelDecode(std::string ms);
	static void IgnoreUntil(std::string fn);
	static void ExecuteScriptuntil(std::string flg);
	static void LoadModule(std::string fn);
	static bool isModel(std::string x);
	static bool SkipCurrentScriptLine();
	static void ForLoop(std::string ini,std::string enf,std::string ite);
};

//MessPack
std::string SpaceErase(std::string line);
std::string CalculationExtend(std::string ex);
bool Compare(std::string x);

