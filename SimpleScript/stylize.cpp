#pragma once
#include "SimpleScript.h"
#include <string>
#include <map>
#include <cctype>
#include <iostream>

std::string equext(std::string ex){
	int ep = ex.find("=");
	//std::cout<<ex<<std::endl;
	while (ex[ep-1] == ' ') {
		ex = ex.substr(0,ep-1) + ex.substr(ep);
		ep = ex.find("=");
	}
	//std::cout<<ex<<std::endl;
	
	while (ex[ep+1] == ' ') {
		ex = ex.substr(0,ep+1) + ex.substr(ep+2);
		ep = ex.find("=");
	}
	//std::cout<<ex<<std::endl;
	
	return ex;
} 
std::string stylize(std::string ln){
	while (ln[0] == '	') ln = ln.substr(1,ln.length()-1);
	while (ln[0] == ' ') ln = ln.substr(1,ln.length()-1);
	if (ln.find("{")) ln[ln.find("{")] = ';';
	if (ln.find("=") != -1){ //Expression
		ln = equext(ln);
	}
	return ln;
}
