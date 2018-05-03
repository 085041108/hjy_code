#ifndef _READINI_H
#define _READINI_H
#include <iostream>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <string.h>
using namespace std;
class readIni
{
public:
	int GetModuleFileName( char* sModuleName, char* sFileName, int nSize);
	int getCnfMess(char* pKey, char* pSave, char* pPath);
};
#endif