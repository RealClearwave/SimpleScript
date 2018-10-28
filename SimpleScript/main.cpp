#pragma once
#include <iostream>
#include <string>
#include "SimpleScript.h"

File cur;

int main(int argc,char* argv[]) {
	graInit();
	cur.ExecuteScript(argv[1]);
	return 0;
}
