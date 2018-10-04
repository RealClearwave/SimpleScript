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
		cur.ln[++cur.size] = stylize(tmp);
		
	fin.close();
}

bool fNext(){
	if (++cur.esp > cur.size) return false;
	
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

void mDec(std::string ms){
	//std::cout<<"Current Esp is :"<<cur.esp<<std::endl;
	cur.fun2ln[ms] =cur.esp;
	fign("^");
}

int  mExe(std::string ms){
	int ln = cur.fun2ln[ms];
	fJump(ln+1);
	return variFetch("retv");
}
