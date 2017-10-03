#include "stdafx.h"
#pragma once 



class CryptoClient
{
	ICrypto* crypto_method;
public:
	void ChangeMethod(ICrypto* ic);
	std::string Encode(const char* text, void* key);
	void Decode(const char* text, void* key);
};