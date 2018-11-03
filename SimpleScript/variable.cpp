#include "SimpleScript.h"
#include <map>
#include <string>
#include <iostream>
const int maxvar = 10001;

std::map<std::string,int> varmp;
int valloc = 0;
int varl[maxvar];

std::string Variable::arrext(std::string x){
	int p0 = x.find("[");
	int p1 = x.find("]");
	if (p0 == -1 || p1 == -1) return x; 
	x[p0] = x[p1] = '_';
	
	std::string vr = x.substr(p0+1,p1-p0-1);
	if (isVari(vr)) {
		
		vr = std::to_string(Fetch(vr));
		x = x.substr(0,p0) + '_' + vr + '_';
	}
	return x;
}

void Variable::Push(std::string x,int org){
	int p0,p1;
	 if ((p0 = x.find("[")) != -1 && (p1 = x.find("]")) != -1){
	 	int num = std::stoi(x.substr(p0+1,p1-p0-1));
	 	for (int i=0;i<=num;i++)
	 		Push(x.substr(0,p0) + "_" + std::to_string(i) + "_",org);
	 		
	 	return;
	 }
	 
	 varmp[x] = valloc;
	 varl[valloc++] = org;
} 

bool Variable::isVari(std::string x){
	x = arrext(x);
	return (varmp.find(x) != varmp.end());
}

void Variable::Clear(std::string x){
	x = arrext(x);
	varl[varmp[x]] = 0;
}
void Variable::Move(std::string x,int mv){
	x = arrext(x);
	if (!isVari(x))
		Push(x,mv);
	else
		varl[varmp[x]] = mv;
}

int Variable::Fetch(std::string x){
	x = arrext(x);
	return varl[varmp[x]];
}

int Variable::Cmp(std::string x,std::string y){
	x = arrext(x);y = arrext(y);
	int a = Fetch(x),b = Fetch(y);
	if (x < y) return LESS;
	if (x == y) return EQUAL;
	if (x > y) return GREATER;
}

