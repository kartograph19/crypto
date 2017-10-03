#include "stdafx.h"
#pragma once 




class ICrypto 
{
protected:
	static const std::string alphabet;
public:
	virtual std::string Encode(const void* text, void* key) = 0;
	virtual void Decode(const void* en_text, void* key) = 0;
};


class CesarCode : public ICrypto
{
public:
	virtual std::string Encode(const void* text, void* key);
	virtual void Decode(const void* en_text, void* key);
};

class Tritemius : public ICrypto
{
	int change_func(int num);
public:
	virtual std::string Encode(const void* text, void* key);
	virtual void Decode(const void* en_text, void* key);
};

class Vizhener : public ICrypto
{
public:
	virtual std::string Encode(const void* text, void* key);
	virtual void Decode(const void* en_text, void* key);
};