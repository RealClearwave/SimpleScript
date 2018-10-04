#include "SimpleScript.h"
#include <string>
#include <fstream>
#define max_lines 10001
struct File{
	std::string ln[max_lines];
	int esp,size;
}cur; 

void fLoad(std::string fn){
	cur.esp = 0;cur.size = 0;
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
	cur.esp = e;
}

void fExe(std::string fn){
	fLoad(fn);
	while (fNext());
	return;
}
