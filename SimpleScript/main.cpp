#include <iostream>
#include <string>
#include "SimpleScript.h"

File CurrentScript;

int main(int argc,char* argv[]) {
	graInit();
	File::ExecuteScript(argv[1]);
	return 0;
}
