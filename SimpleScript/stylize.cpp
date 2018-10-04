#include "SimpleScript.h"
#include <string>
#include <map>
#include <cctype>
#include <iostream>

std::string stylize(std::string ln){
	while (ln[0] == '	') ln = ln.substr(1,ln.length()-1);
	while (ln[0] == ' ') ln = ln.substr(1,ln.length()-1);
	if (ln.find("{")) ln[ln.find("{")] = ';';
	return ln;
}
