#include "SimpleScript.h"
#include <string>
#include <fstream>
#include <iostream>
#define max_lines 10001
struct File{
	std::string ln[max_lines];
	int esp,size;
	int rtl[max_lines],rtc;
}cur; 

void fLoad(std::string fn){
	cur.esp = 0;cur.rtc = 0;cur.size = 0;
	cur.rtl[++cur.rtc] = 0;
	std::string tmp;
	std::ifstream fin(fn.c_str());
	while (fin>>tmp)
		cur.ln[++cur.size] = tmp;
		
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
