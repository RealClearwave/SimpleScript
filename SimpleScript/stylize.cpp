#include "SimpleScript.h"
#include <string>
#include <map>
#include <cctype>
#include <iostream>

std::string equext(std::string ex){
	int ep = ex.find("=");
	while (ex[ep-1] == ' ') {
		ex = ex.substr(0,ep-1) + ex.substr(ep);
		ep = ex.find("=");
	}
	
	while (ex[ep+1] == ' ') {
		ex = ex.substr(0,ep+1) + ex.substr(ep+2);
		ep = ex.find("=");
	}
	
	return ex;
} 

std::string fncext(std::string ex){
	int ep = ex.find("(");
	while (ex[ep-1] == ' ') {
		ex = ex.substr(0,ep-1) + ex.substr(ep);
		ep = ex.find("(");
	}
	
	return ex;
} 

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

std::string stylize(std::string ln){
	if (ln == "}^{") return ln;
	while (ln[0] == '	') ln = ln.substr(1,ln.length()-1);
	while (ln[0] == ' ') ln = ln.substr(1,ln.length()-1);
	if (ln.find("{")) ln[ln.find("{")] = ';';
	
	if (ln.find("=") != -1) //Expression
		ln = equext(ln);
	if (ln.find("(") != -1)
		ln = fncext(ln);
		
	if (isCal(ln)){
			std::string lf = ln.substr(ln.find("=")+1);
			ln = ln.substr(0,ln.find("=")+1) + calext(lf);
	}
	
	return ln;
}
