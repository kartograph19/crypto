#include "stdafx.h"

#pragma once




void CodeClient::ShowBytes()
{
	cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
	encoder->getCode(text.get());
	cout<<endl;
	encoder->getString();
	cout<<endl<<"-------------------------------------------------------------------------------"<<endl;
}

void CodeClient::ChangeCode(IEncoder* en)
{
	encoder.reset(en);
}

void CodeClient::callThread()
{
	//thread th1(bind(&CodeClient::ShowBytes,this));	
	thread th1 (&CodeClient::ShowBytes,this);
	th1.join();
}


