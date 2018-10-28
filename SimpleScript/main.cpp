#pragma once
#include <iostream>
#include <string>
#include "SimpleScript.h"

File CurrentScript;

int main(int argc,char* argv[]) {
	graInit();
	CurrentScript.ExecuteScript(argv[1]);
	return 0;
}
