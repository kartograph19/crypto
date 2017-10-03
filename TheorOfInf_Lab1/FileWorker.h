#pragma once


#include "stdafx.h"


class FileWorker
{
	FILE* file;
	char* buffer;
	std::vector<MessageElement> symbols;
	void removeSpave(char* str,bool (*check)(char delim));
	void entropy();
public:
	FileWorker(char*,IEncoder*);
	void Encode();
	void Decode();
};