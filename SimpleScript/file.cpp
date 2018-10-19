#include "SimpleScript.h"
#include <string>
#include <fstream>
#include <iostream>
#include <map>
#define max_lines 10001
#define max_mods 301
 
struct File{
	std::string ln[max_lines];
	int esp,size;
	int rtl[max_lines],rtc;
	std::map<std::string,int> fun2ln;
}cur; 

void fLoad(std::string fn){
	cur.esp = 0;cur.rtc = 0;cur.size = 0;
	cur.rtl[++cur.rtc] = 0;
	std::string tmp;
	std::ifstream fin(fn.c_str());
	while (getline(fin,tmp))
		cur.ln[++cur.size] = tmp;
	
	cur.ln[++cur.size] = "exit();";
	fin.close();
}

bool fNext(){
	if (++cur.esp > cur.size) return false;
	//std::cout<<cur.esp<<' '<<cur.ln[cur.esp]<<std::endl;
	graDentify(cur.ln[cur.esp]);
	return true;
}

void fJump(int e){
	cur.rtl[++cur.rtc] = cur.esp;
	cur.esp = e-1;
	//std::cout<<"Jumped to Esp "<<cur.esp+1<<std::endl;
}

void fRet(){
	cur.esp = cur.rtl[cur.rtc];
	cur.rtc--;
	//std::cout<<"Return back with esp:"<<cur.esp<<std::endl;
}

void fExe(std::string fn){
	fLoad(fn);
	while (fNext());
	return;
}

void fign(std::string fn){
	while (cur.ln[cur.esp] != fn) cur.esp++;
	//std::cout<<"fign to esp:"<<cur.esp<<std::endl;
}

void fExeuntil(std::string flg){
	//std::cout<<"Entered f with "<<cur.ln[cur.esp]<<std::endl;
	int te = cur.esp;cur.esp++;
	while (cur.ln[cur.esp] != flg){
		//std::cout<<cur.ln[cur.esp]<<std::endl;
		graDentify(cur.ln[cur.esp]);
		
		if (cur.ln[cur.esp].find("return") != -1)
			break;
		
		
		cur.esp++;
	}
	
	//std::cout<<"Loop back at "<<te<<std::endl;
	cur.esp = te;
}
void mDec(std::string ms){
	//std::cout<<"Current Esp is :"<<cur.esp<<std::endl;
	cur.fun2ln[ms] =cur.esp;
	fign("}");
}

int  mExe(std::string argv[]){
	int ln = cur.fun2ln[argv[0]],i = 0;
	while (argv[++i] != ""){
		//std::cout<<argv[i]<<' '<<i<<std::endl;
		std::string tmp = argv[0] + "_" + std::to_string(i) + "_";
		//std::cout<<tmp<<" Created."<<std::endl;
		if (!isVari(tmp)) variPush(tmp,std::stoi(argv[i])); else variMove(tmp,std::stoi(argv[i]));
	}
	
	i--;
	std::string tmp = argv[0] + "argc";
	//std::cout<<tmp<<' '<<i<<std::endl;
	if (!isVari(tmp)) variPush(tmp,i); else variMove(tmp,i);
	
	int te = cur.esp;
	cur.esp = ln;fExeuntil("}");
	//std::cout<<"G:"<<variFetch("retv")<<std::endl;
	cur.esp = te;
	return variFetch("retv");
}

void ldmod(std::string fn){
	fn += ".fmd";//std::cout<<fn<<std::endl;
	std::ifstream fin(fn.c_str());
	std::string tmp;
	
	while (getline(fin,tmp)){
		cur.ln[++cur.size] = stylize(tmp);
		std::string t = cur.ln[cur.size];
		if (t.find("decl") != -1){
			int p0 = t.find("("),p1 = t.find(")");
			std::string k = t.substr(p0+1,p1-p0-1);
			//std::cout<<k<<' '<<cur.size+1<<std::endl;
			cur.fun2ln[k] = cur.size;
		}
	}
	
	return;
} 
