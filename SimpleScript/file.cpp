#pragma once
#include "SimpleScript.h"
#include <string>
#include <fstream>

void File::TruncFile(std::string x){
	int pos,last = 0;
	while ((pos = x.find(';',last)) != -1){
		CurrentScript.ln.push_back(line());
		CurrentScript.ln.back().push(x.substr(last,pos-last));
		last = pos+1;
	}
}

std::string File::LoadFile(std::string fn){
	CurrentScript.esp = -1;CurrentScript.rtc = 0;
	CurrentScript.rtl[++CurrentScript.rtc] = 0;
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

bool File::SkipCurrentScriptrentLine(){
	CurrentScript.esp++;
}
bool File::ExecuteNextLine(){
	if (++CurrentScript.esp > CurrentScript.ln.size()) return false;
	CurrentScript.ln[CurrentScript.esp].exec();
	return true;
}

void File::JumpToLine(int e){
	CurrentScript.rtl[++CurrentScript.rtc] = CurrentScript.esp;
	CurrentScript.esp = e-1;
}

void File::DeclReturn(){
	CurrentScript.esp = CurrentScript.rtl[CurrentScript.rtc];
	CurrentScript.rtc--;
}

void File::ExecuteScript(std::string fn){
	TruncFile(LoadFile(fn));
	while (ExecuteNextLine());
	return;
}

void File::IgnoreUntil(std::string fn){
	while (CurrentScript.ln[++CurrentScript.esp].str() != fn);
		//std::cout<<"[Ignore]"<<CurrentScript.ln[CurrentScript.esp].str()<<std::endl;
}

void File::ExecuteScriptuntil(std::string flg){
	int te = CurrentScript.esp;CurrentScript.esp++;
	while (CurrentScript.ln[CurrentScript.esp].str() != flg){
		//std::cout<<CurrentScript.ln[CurrentScript.esp].str()<<','<<flg<<std::endl;
		CurrentScript.ln[CurrentScript.esp].exec();
		if (CurrentScript.ln[CurrentScript.esp].str().find("return") != -1) break;
		
		CurrentScript.esp++;
	}
	
	//std::cout<<"[finished]"<<std::endl;
	CurrentScript.esp = te;
}
void File::ModelDecode(std::string ms){
	CurrentScript.fun2ln[ms] =CurrentScript.esp;
	IgnoreUntil("}");
}

int  File::ModelExecute(std::string argv[]){
	int ln = CurrentScript.fun2ln[argv[0]],i = 0;
	while (argv[++i] != ""){
		std::string tmp = argv[0] + "_" + std::to_string(i) + "_";
		if (!Variable::isVari(tmp)) Variable::Push(tmp,std::stoi(argv[i]));
		else Variable::Move(tmp,std::stoi(argv[i]));
	}
	
	i--;
	std::string tmp = argv[0] + "argc";
	if (!Variable::isVari(tmp)) Variable::Push(tmp,i); else Variable::Move(tmp,i);
	
	int te = CurrentScript.esp;
	CurrentScript.esp = ln;ExecuteScriptuntil("}");
	CurrentScript.esp = te;
	return Variable::Fetch("retv");
}

bool File::isModel(std::string x){
	return (CurrentScript.fun2ln.find(x) != CurrentScript.fun2ln.end());
}
void File::LoadModule(std::string fn){
	fn += ".fmd";
	std::ifstream fin(fn.c_str());
	std::string tmp;
	
	while (getline(fin,tmp)){
		CurrentScript.ln.back().push(tmp);
		std::string t = CurrentScript.ln.back().str();
		if (t.find("decl") != -1){
			int p0 = t.find("("),p1 = t.find(")");
			std::string k = t.substr(p0+1,p1-p0-1);
			CurrentScript.fun2ln[k] = CurrentScript.ln.size();
		}
	}
	
	return;
} 
