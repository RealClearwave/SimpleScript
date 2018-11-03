#include "SimpleScript.h"
#include <string>
#include <map>
#include <cctype>
#include <iostream>

std::string CalculationExtend(std::string ex){
	if (!isCal(ex)) return ex;
	int op = isCal(ex);
	std::string ret,lf = ex.substr(0,op),rt = ex.substr(op+1);
	lf = CalculationExtend(lf),rt = CalculationExtend(rt);
	if (ex[op] == '+') ret = "add(" + lf + "," + rt + ")";
	if (ex[op] == '-') ret = "sub(" + lf + "," + rt + ")";
	if (ex[op] == '*') ret = "mul(" + lf + "," + rt + ")";
	if (ex[op] == '/') ret = "div(" + lf + "," + rt + ")";
	return ret;
}

std::string SpaceErase(std::string line){
	while (line[0] == '	') line = line.substr(1,line.length()-1);
	while (line[0] == ' ') line = line.substr(1,line.length()-1);
	return line; 
}

bool Compare(std::string x){
	int pos = x.find('#');
	if (pos == -1) pos = x.find('>');
	if (pos == -1) pos = x.find('<');
	if (pos == -1) return false;
	
	std::string lf = x.substr(0,pos),rf = x.substr(pos+1);
	int lv,rv;
	if (Variable::isVari(lf)) lv = Variable::Fetch(lf); else lv = std::stoi(lf);
	if (Variable::isVari(rf)) rv = Variable::Fetch(rf); else rv = std::stoi(rf);
	//std::cout<<lv<<' '<<rv<<' '<<pos<<"\n"; 
	if (x[pos] == '#')
		return (lv == rv);
	else if (x[pos] == '>')
		return (lv > rv);
	else if (x[pos] == '<')
		return (lv < rv);
} 
