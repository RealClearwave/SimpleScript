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
	bool SkipCurrentScriptrentLine();
};

extern File CurrentScript; 

//Stylize
std::string SpaceErase(std::string line);
std::string CalculationExtend(std::string ex);
