#include <map>
#include <iostream>
#include "SimpleScript.h"

std::string id2str[maxfunc] = {
	"print","println","delay","isvari","decv","add","input",
	"comp","if","goto","endl","rand","sub","mul",
	"div","popback","exit","decl","call","for","import",
	"_sys","return","<end>"
};
std::map <std::string,int> gramp;

char trset[_maxtr]{
	' ','	',',','(',')',
	'=','{','\0'
};
std::map<char,bool> trs;
	
void graInit(){
	int i = -1;
	while (id2str[++i] != "<end>"){
		gramp[id2str[i]] = i;
	}
	
	for (int i=0;trset[i];i++)
		trs[trset[i]] = true;
}

bool isFunc(std::string x){
	return (gramp.find(x) != gramp.end());
} 

bool isNum(std::string x){
	if (x.length() == 0) return false;
	for (int i=0;i<x.length();i++)
		if (x[i]<'0' || x[i] > '9') return false;
	
	return true;
}

int isCal(std::string x){
	if (x.find("*") != -1) return x.find("*");
	if (x.find("/") != -1) return x.find("/");
	if (x.find("+") != -1) return x.find("+");
	if (x.find("-") != -1) return x.find("-");
	return false;
} 

bool isRet(std::string &x){
	int lf = x.find('(');
	int eq = x.find('=');
	int ek = x.find("==");
	if (eq == ek) return false;
	if (eq == -1) return false;
	if (lf != -1 && lf < eq) return false;
	
	x[eq] = ' ';
	return true;
}

bool line::push(std::string x){
	to_str = x;
	int i = 0,last = 0;pts = -1;argc = -1;
	
	while (i < x.length() && trs.find(x[i]) != trs.end()) last++,i++;
	while (i < x.length()){
		while (i < x.length() && trs.find(x[i]) == trs.end()) i++;
		trunc[++pts] = x.substr(last,i-last);
		if (i >= x.length()) break;
		while (i < x.length() && trs.find(x[i]) != trs.end()) i++;
		last = i;
	}

	i = 0;if (isRet(x)) va = trunc[i++];
	if (isNum(trunc[i]) || isVari(trunc[i])){
		argc = 1;
		argv[0] = trunc[i];argv[1] = "0";
		func = "add";
		return true;
	}else if (isFunc(trunc[i]) || isMod(trunc[i])) {
		func = trunc[i];
		while (++i <= pts){
			argv[++argc] = trunc[i];
		}
		return true;
	}else
		return false;
		
	return true;
}
	
std::string line::exec(){
	std::string ag[_maxtr];
	for (int i=0;i<=argc;i++) ag[i] = argv[i];
	
	for (int i=0;i<=argc;i++){
		if (ag[i][0] == '"')
			ag[i] = ag[i].substr(1,ag[i].length()-2);
		else if (ag[i][0] == '&')
			ag[i] = ag[i].substr(1,ag[i].length()-1);	
		else if (isCal(ag[i])) {
				ag[i] = calext(ag[i]);
				ag[i] = execl(ag[i]);
		}else if (isNum(ag[i])){
			//std::cout<<ag[i]<<" is a number"<<std::endl;
		}else if (isVari(ag[i])){
				ag[i] = std::to_string(variFetch(ag[i]));
		}else if (exeable(ag[i]))
			ag[i] = execl(ag[i]);
			
	}
	
	int ret;
	if (isFunc(func))
		ret = execPro(gramp[func],ag);
	else{
		std::string ag0[maxarg];
		ag0[0] = func;
		for (int i=0;i<=argc;i++)
			ag0[i+1] = ag[i];
			
		ret = mExe(ag0);
	}
	
	if (isRet(to_str)) variMove(va,ret);
	return std::to_string(ret);
}	

bool exeable(std::string x){
	line tmp;
	return tmp.push(x);
}
std::string execl(std::string x){
	line tmp;
	tmp.push(x);
	return tmp.exec();
}	
