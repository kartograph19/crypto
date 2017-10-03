#include "stdafx.h"

std::string CryptoClient::Encode(const char* text, void* key)
{
	auto text_coded = this->crypto_method->Encode(text,key);
	cout<<text_coded<<endl;
	return text_coded;
}

void CryptoClient::Decode(const char* text, void* key)
{
	this->crypto_method->Decode(text,key);
}

void CryptoClient::ChangeMethod(ICrypto* ic)
{
	this->crypto_method  = ic;
}