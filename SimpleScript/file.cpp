#include "SimpleScript.h"
#include <string>
#include <iostream>
#include <fstream>

std::vector<line> ln;
int esp;
int rtl[max_lines],rtc;
std::map<std::string,int> fun2ln;
	
void File::TruncFile(std::string x){
	int pos,last = 0;
	while ((pos = x.find(';',last)) != -1){
		ln.push_back(line());
		ln.back().push(x.substr(last,pos-last));
		last = pos+1;
	}
}

std::string File::LoadFile(std::string fn){
	esp = -1;rtc = 0;
	rtl[++rtc] = 0;
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

bool File::SkipCurrentScriptLine(){
	esp++;
}
bool File::ExecuteNextLine(){
	if (++esp > ln.size()) return false;
	ln[esp].exec();
	return true;
}

void File::JumpToLine(int e){
	rtl[++rtc] = esp;
	esp = e-1;
}

void File::DeclReturn(){
	esp = rtl[rtc];
	rtc--;
}

void File::ExecuteScript(std::string fn){
	TruncFile(LoadFile(fn));
	while (ExecuteNextLine());
	return;
}

void File::IgnoreUntil(std::string fn){
	while (!ln[++esp].contain(fn));
		//std::cout<<"[Ignore]"<<ln[esp].str()<<std::endl;
}

void File::ExecuteScriptuntil(std::string flg){
	int te = esp;esp++;
	while (!ln[esp].contain(flg)){
		//std::cout<<esp<<' '<<ln[esp].str()<<' '<<ln[esp].good<<std::endl;
		if (ln[esp].good) ln[esp].exec();
		if (ln[esp].str().find("return") != -1) break;
		
		esp++;
	}
	
	//std::cout<<"[finished]"<<std::endl;
	esp = te;
}
void File::ModelDecode(std::string ms){
	fun2ln[ms] =esp;
	IgnoreUntil("}");
}

int  File::ModelExecute(std::string argv[]){
	int ln = fun2ln[argv[0]],i = 0;
	while (argv[++i] != ""){
		std::string tmp = argv[0] + "_" + std::to_string(i) + "_";
		if (!Variable::isVari(tmp)) Variable::Push(tmp,std::stoi(argv[i]));
		else Variable::Move(tmp,std::stoi(argv[i]));
	}
	
	i--;
	std::string tmp = argv[0] + "argc";
	if (!Variable::isVari(tmp)) Variable::Push(tmp,i); else Variable::Move(tmp,i);
	
	int te = esp;
	esp = ln;ExecuteScriptuntil("}");
	esp = te;
	return Variable::Fetch("retv");
}

bool File::isModel(std::string x){
	return (fun2ln.find(x) != fun2ln.end());
}

void File::LoadModule(std::string fn){
	fn += ".fmd";
	std::ifstream fin(fn.c_str());
	std::string tmp;
	
	while (getline(fin,tmp)){
		ln.back().push(tmp);
		std::string t = ln.back().str();
		if (t.find("decl") != -1){
			int p0 = t.find("("),p1 = t.find(")");
			std::string k = t.substr(p0+1,p1-p0-1);
			fun2ln[k] = ln.size();
		}
	}
	
	return;
} 

void File::ForLoop(std::string ini,std::string enf,std::string ite){
	//std::cout<<ini<<' '<<enf<<' '<<ite<<std::endl;
	execl(ini);
	//std::cout<<Compare("4<11")<<std::endl;
	while (Compare(enf)){
		//std::cout<<"#"<<enf<<' '<<Variable::Fetch("i")<<"#"<<std::endl;
		ExecuteScriptuntil("}");
		execl(ite);
	}
	
	IgnoreUntil("}");
	//SkipCurrentScriptLine();
}
