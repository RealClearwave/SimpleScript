#include "SimpleScript.h"
#include <string>
#include <map>
#include <cctype>
#include <iostream>

std::string calext(std::string ex){
	if (!isCal(ex)) return ex;
	int op = isCal(ex);
	std::string ret,lf = ex.substr(0,op),rt = ex.substr(op+1);
	lf = calext(lf),rt = calext(rt);
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
