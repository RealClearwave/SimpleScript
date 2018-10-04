#include "SimpleScript.h"
#include <map>
#include <string>
const int maxvar = 10001;

std::map<std::string,int> varmp;
int valloc = 0;
int varl[maxvar];

void variPush(std::string x,int org){
	 varmp[x] = valloc;
	 varl[valloc++] = org;
} 

bool isVari(std::string x){
	return (varmp.find(x) != varmp.end());
}

void variMove(std::string x,int mv){
	varl[varmp[x]] = mv;
}

int variFetch(std::string x){
	return varl[varmp[x]];
}

void variAdd(std::string x,std::string a){
	if (isVari(a))
		variMove(x,variFetch(x) + variFetch(a));
	else
		variMove(x,variFetch(x) + std::stoi(a.c_str()));
}

void variMul(std::string x,std::string a){
	if (isVari(a))
		variMove(x,variFetch(x) * variFetch(a));
	else
		variMove(x,variFetch(x) * std::stoi(a.c_str()));
}

int variCmp(std::string x,std::string y){
	int a = variFetch(x),b = variFetch(y);
	if (x < y) return LESS;
	if (x == y) return EQUAL;
	if (x > y) return GREATER;
}

