#pragma once
#include "SimpleScript.h"
#include <string>
#include <fstream>

void File::TruncFile(std::string x){
	int pos,last = 0;
	while ((pos = x.find(';',last)) != -1){
		cur.ln.push_back(line());
		cur.ln.back().push(x.substr(last,pos-last));
		last = pos+1;
	}
}

std::string File::LoadFile(std::string fn){
	cur.esp = -1;cur.rtc = 0;
	cur.rtl[++cur.rtc] = 0;
	std::string tmp,ret;
	std::ifstream fin(fn.c_str());
	while (getline(fin,tmp)){
		ret += tmp;
		if (ret[ret.length()-1] != ';') ret += ';';
	}

	ret += "exit();";
	fin.close();
	return ret;
}

bool File::SkipCurrentLine(){
	cur.esp++;
}
bool File::ExecuteNextLine(){
	if (++cur.esp > cur.ln.size()) return false;
	cur.ln[cur.esp].exec();
	return true;
}

void File::JumpToLine(int e){
	cur.rtl[++cur.rtc] = cur.esp;
	cur.esp = e-1;
}

void File::DeclReturn(){
	cur.esp = cur.rtl[cur.rtc];
	cur.rtc--;
}

void File::ExecuteScript(std::string fn){
	TruncFile(LoadFile(fn));
	while (ExecuteNextLine());
	return;
}

void File::IgnoreUntil(std::string fn){
	while (cur.ln[++cur.esp].str() != fn);
		//std::cout<<"[Ignore]"<<cur.ln[cur.esp].str()<<std::endl;
}

void File::ExecuteScriptuntil(std::string flg){
	int te = cur.esp;cur.esp++;
	while (cur.ln[cur.esp].str() != flg){
		//std::cout<<cur.ln[cur.esp].str()<<','<<flg<<std::endl;
		cur.ln[cur.esp].exec();
		if (cur.ln[cur.esp].str().find("return") != -1) break;
		
		cur.esp++;
	}
	
	//std::cout<<"[finished]"<<std::endl;
	cur.esp = te;
}
void File::ModelDecode(std::string ms){
	cur.fun2ln[ms] =cur.esp;
	IgnoreUntil("}");
}

int  File::ModelExecute(std::string argv[]){
	int ln = cur.fun2ln[argv[0]],i = 0;
	while (argv[++i] != ""){
		std::string tmp = argv[0] + "_" + std::to_string(i) + "_";
		if (!isVari(tmp)) variPush(tmp,std::stoi(argv[i])); else variMove(tmp,std::stoi(argv[i]));
	}
	
	i--;
	std::string tmp = argv[0] + "argc";
	if (!isVari(tmp)) variPush(tmp,i); else variMove(tmp,i);
	
	int te = cur.esp;
	cur.esp = ln;ExecuteScriptuntil("}");
	cur.esp = te;
	return variFetch("retv");
}

bool File::isModel(std::string x){
	return (cur.fun2ln.find(x) != cur.fun2ln.end());
}
void File::LoadModule(std::string fn){
	fn += ".fmd";
	std::ifstream fin(fn.c_str());
	std::string tmp;
	
	while (getline(fin,tmp)){
		cur.ln.back().push(tmp);
		std::string t = cur.ln.back().str();
		if (t.find("decl") != -1){
			int p0 = t.find("("),p1 = t.find(")");
			std::string k = t.substr(p0+1,p1-p0-1);
			cur.fun2ln[k] = cur.ln.size();
		}
	}
	
	return;
} 
