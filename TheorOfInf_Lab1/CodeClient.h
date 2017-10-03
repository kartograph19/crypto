

#pragma once 

#include "IEncoder.h"
#include "stdafx.h"


class CodeClient
{
	std::shared_ptr<IEncoder>encoder;
	std::unique_ptr<char> text;
public:
	void callThread();
	CodeClient(IEncoder* ie,char * t, size_t len):encoder(ie),text(t)
	{
	}
	void ShowBytes();
	void ChangeCode(IEncoder* en);
};




















