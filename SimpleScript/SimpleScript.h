#include <string>
const std::string VERS = "1.4c";

//calling procedures
const int  maxarg = 1001;
const int  maxfunc= 1001;
int execPro(int id, ...);
int execPro(int id, std::string argv[]);
//Grammar
void graInit();
void graDentify(std::string x); 

//Variable
void variPush(std::string x,int org = 0);
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
void fLoad(std::string fn);
bool fNext();
void fJump(int e);
void fExe(std::string fn);

