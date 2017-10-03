// TheorOfInf_Lab1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int _tmain(int argc, _TCHAR* argv[])
{
	


	{
		system("chcp 1251");
		
		char* text = new char[256];
		cout<<"Enter text to code: ";
		cin.getline(text,256);
		int len = strlen(text);
		CryptoClient cc; 
		cc.ChangeMethod(new CesarCode);
		int c_key;
		cout<<"Enter key for Cesar: ";
		cin>>c_key;
		cout<<"Cesar: ";
		std::string c_text = cc.Encode(text, &c_key);
		cc.Decode(c_text.data(),&c_key);

		cout<<endl<<"Tritemius: ";
		cc.ChangeMethod(new Tritemius);
		c_text = cc.Encode(text, NULL);
		cc.Decode(c_text.data(),NULL);

		cout<<endl<<"Vizhener: "<<endl;
		cc.ChangeMethod(new Vizhener);
		char* key = new char[256];
		cout<<"Key for Vizhener: ";
		cin.ignore();
		cin.getline(key,256);
		c_text = cc.Encode(text,key);
		cc.Decode(c_text.data(), key);

		delete[] text;
		delete[] key;
	//	char* text = new char[256];
	//	cout<<"Enter text to code: ";
	//	cin.getline(text,256);
	////	strcpy(text,"Yagodzisnki");
	//	int len = strlen(text);
	//	cout<<"Symbols to code: ";
	//	for(int i = 0; i<len;i++)
	//		cout<<(int)((unsigned char)text[i])<<" ";
	//	cout<<endl;
	
	/*	CodeClient cd(new Haffman,text,strlen(text));
		cd.callThread();*/


	//	cd.callThread();
	//	cout<<endl;
	//	cd.ChangeCode(new BCDEncoder);
	//	cd.callThread();
	//	cout<<endl;
	//	cd.ChangeCode(new BergerEncoder);
	//	cd.callThread();
	//	cout<<endl;
	//	cd.ChangeCode(new ModQCheckingEncoder);
	//	cd.callThread();
	//	cout<<endl;
	//	cd.ChangeCode(new RepeatedNumberEncoder);
	//	cd.callThread();
	//	cout<<endl;
	//	cd.ChangeCode(new IterativeEndcoder);
	//	cd.callThread();
	//	cout<<endl;
	//	cd.ChangeCode(new ElaesEndcoder);
	//	cd.callThread();
	
		

	}

	
	_getch();
	return 0;
}

