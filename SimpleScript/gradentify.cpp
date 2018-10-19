//Grammer Identify
#pragma once
#include <map>
#include <iostream>
#include "SimpleScript.h"

std::string id2str[maxfunc] = {
	"print","println","delay","isvari","decv","add","input",
	"comp","if","goto","endl","rand","sub","mul",
	"div","return","exit","decl","call","for","import",
	"_sys"
};
std::map <std::string,int> gramp;

void graInit(){
	int i = -1;
	while (id2str[++i] != ""){
		gramp[id2str[i]] = i;
	}
}

bool isFunc(std::string x){
	return (gramp.find(x) != gramp.end());
} 

bool isNum(std::string x){
	if (x.length() == 0) return false;
	for (int i=0;i<x.length();i++)
		if (x[i] != '[' && x[i] != ']' && (x[i]<'0' || x[i] > '9')) return false;
	
	return true;
}

int isCal(std::string x){
	if (x.find("*") != -1) return x.find("*");
	if (x.find("/") != -1) return x.find("/");
	if (x.find("+") != -1) return x.find("+");
	if (x.find("-") != -1) return x.find("-");
	return false;
} 

std::string graDentify(std::string x){ 
	x = stylize(x);
	//std::cout<<x<<std::endl;
	if (x.length() == 0) return "0";
	if (x[0] == '#') return "Remarked";
	if (x.find(";") == -1 && x.find("=") == -1){
		//std::cout<<x<<' '<<isVari(x)<<std::endl;
		if (x[0] == '&') return x.substr(1,x.length()-1);
		else if (isVari(x)) return std::to_string(variFetch(x));
		else if (isCal(x)) return calext(x);
		else if (x.find("(") != -1) x += ";";
		else return x;
	}
	
	std::string v,c,a,tmp;
	bool isret = false; 
	int cma = x.find(";"),ef;
	if (cma == -1) {
		isret = true;
		ef = x.find("=");
		v = x.substr(0,ef);
		if (!isVari(v)) variPush(v,0);
		
	}else{
		ef = -1;
	}
	
	tmp = x.substr(ef+1);
	int lf = tmp.find("(");
	
	if (lf == -1 && ef != -1){
		a = tmp;
		if (isVari(a)){
			variMove(v,variFetch(a));
			return a;
		}
		if (isNum(a)){
			//std::cout<<a<<std::endl;
			variMove(v,std::stoi(a));
			return a;
		}
	}
	
	c = tmp.substr(0,lf);
	a = tmp.substr(lf+1);
	if (a[a.length()-1] == ';') a = a.substr(0,a.length()-1);
	if (a[a.length()-1] == ')') a = a.substr(0,a.length()-1);
	
	//std::cout<<v<<'_'<<c<<'_'<<a<<std::endl;
	//std::cout<<std::endl;
	
	int last = 0,argc = 0;
	std::string argv[maxarg];
	for (int i=0;i<a.length();i++){
		if (a[i] == '(') while (a[i] != ')') i++;
		if (a[i] == '"') {last++;i++;while (a[i] != '"') i++;a[i] = ' ';}
		if (a[i] == ','){
			argv[argc++] = a.substr(last,i-last);
			last = i+1;
		}
	}
	
	argv[argc] = a.substr(last);
	
	for (int i=0;i<=argc;i++){
		argv[i] = graDentify(argv[i]);
		//std::cout<<argv[i]<<' ';
	} 
	
	//int cid = gramp[c];
	int ret = -2147;
	if (isFunc(c))
		ret = execPro(gramp[c],argv); 
	else{
		std::string ag[maxarg];
		ag[0] = c;//std::cout<<argc<<std::endl;
		for (int k=1;k<=argc+1;k++)
			ag[k] = argv[k-1];
		
		//std::cout<<ag[0]<<' '<<ag[1]<<' '<<ag[2]<<std::endl;
		ret = mExe(ag);
	}
	
	if (isret){
		variMove(v,ret);
	}
	
	//std::cout<<v<<' '<<ret<<std::endl;
	return std::to_string(ret);
}
