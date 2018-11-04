#include <map>
#include <iostream>
#include "SimpleScript.h"

std::string id2str[maxfunc] = {
	"print","println","delay","isvari","decv","add","input",
	"comp","if","goto","endl","rand","sub","mul",
	"div","popback","exit","decl","call","for","import",
	"_sys","return","else","<end>"
};
std::map <std::string,int> gramp;

char trset[_maxtr]{
	' ','	',',','(',')',
	'{','\0'
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
	if (lf == -1 && eq != -1){
		x[eq] = ' ';
		return true;
	}
	
	if (eq == -1 || lf < eq) return false;
	
	x[eq] = ' ';
	return true;
}

bool line::contain(std::string x){
	return (func == x);
}

bool line::push(std::string x){
	x = SpaceErase(x);
	to_str = x;isret = isRet(x);
	int i = 0,last = 0;pts = -1;argc = -1;
	
	while (i < x.length() && trs.find(x[i]) != trs.end()) last++,i++;
	while (i < x.length()){
		if (x[i] == '\"'){
			pts++;
			while (x[++i] != '\"') trunc[pts] += x[i];
			trunc[pts] = '\"' + trunc[pts] + x[i++];
			//std::cout<<"HA"<<trunc[pts]<<"HB"<<std::endl;
			last = i;
		}else {
			while (i < x.length() && trs.find(x[i]) == trs.end()) i++;
			trunc[++pts] = x.substr(last,i-last);
		}
		
		if (i >= x.length()) break;
		while (i < x.length() && trs.find(x[i]) != trs.end()) i++;
		last = i;
	}

	//for (int i=0;i<=pts;i++) std::cout<<trunc[i]<<' ';
	//std::cout<<std::endl;
	
	i = 0;if (isret) va = trunc[i++];
	if (int pos = isCal(trunc[i])){
		std::string lf = trunc[i].substr(0,pos), \
					rf = trunc[i].substr(pos+1);
					
		switch(trunc[i][pos]){
			case '+':{
				func = "add";break;
			}
			case '-':{
				func = "sub";break;
			}
			case '*':{
				func = "mul";break;
			}
			case '/':{
				func = "div";break;
			}
		}
		argv[0] = lf;
		argv[1] = rf;
		argc = 1;
		//std::cout<<func<<' '<<lf<<' '<<rf<<std::endl;
		good = true;
		return true;
	}
	//std::cout<<trunc[i]<<std::endl;
	if (isNum(trunc[i]) || Variable::isVari(trunc[i])){
		
		argc = 1;
		argv[0] = trunc[i];argv[1] = "0";
		func = "add";
		good = true;
		return true;
	}else if (isFunc(trunc[i]) || File::isModel(trunc[i])) {
		func = trunc[i];
		while (++i <= pts){
			argv[++argc] = trunc[i];
		}
		good = true;
		return true;
	}else{
		func = trunc[i];
		good = false;
		return false;
	};
}
	
std::string line::exec(){
	//std::cout<<func<<std::endl; 
	std::string ag[_maxtr];
	for (int i=0;i<=argc;i++) ag[i] = argv[i];
	
	for (int i=0;i<=argc;i++){ 
		if (ag[i][0] == '"')
			ag[i] = ag[i].substr(1,ag[i].length()-2);
		else if (ag[i][0] == '&')
			ag[i] = ag[i].substr(1,ag[i].length()-1);	
		else if (isCal(ag[i])) {
			ag[i] = CalculationExtend(ag[i]);
			ag[i] = execl(ag[i]);
		}else if (isNum(ag[i])){
			//std::cout<<ag[i]<<" is a number"<<std::endl;
		}else if (Variable::isVari(ag[i])){
			ag[i] = std::to_string(Variable::Fetch(ag[i]));
		}else if (exeable(ag[i]))
			ag[i] = execl(ag[i]);
		
		//std::cout<<ag[i]<<',';
	}
	
	//std::cout<<std::endl;
	int ret;
	if (isFunc(func))
		ret = execPro(gramp[func],ag);
	else{
		//std::cout<<to_str<<std::endl;
		std::string ag0[maxarg];
		ag0[0] = func;
		for (int i=0;i<=argc;i++)
			ag0[i+1] = ag[i];
			
		ret = File::ModelExecute(ag0);
	}
	
	//std::cout<<ret<<std::endl;
	if (isret) Variable::Move(va,ret);
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
