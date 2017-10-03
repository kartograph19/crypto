#include "stdafx.h"



FileWorker::FileWorker(char* name ,IEncoder* en)
{
	file = fopen(name,"rb");
	buffer = new char[BUFF_SIZE];
}


void FileWorker::Encode()
{
	int des = _fileno(file);
	int len = _filelength(des);
	int size = 0;
	for(int i = 0;i<len/BUFF_SIZE;i++)
	{
		size = fread(buffer,1,BUFF_SIZE,file);
		if(size!=BUFF_SIZE)
			cout<<endl<<endl<<ferror(file)<<endl<<endl;
	//	this->removeSpave(buffer);
		for(int j = 0; j<BUFF_SIZE;j++)
		{
			int size_s = this->symbols.size();	
			if(std::find(symbols.begin(),symbols.end(),buffer[j]) == symbols.end())
			{
				MessageElement me(buffer[j],size);  
				symbols.push_back(me);
				for(int k = j+1; k<size; k++)
					if(buffer[k] == buffer[j])
						symbols[symbols.size()-1].IncreaseC();
			}
		}
	}
	
	size = len%BUFF_SIZE;
	fread(buffer,1,len%BUFF_SIZE,file);
	//this->removeSpave(buffer);
	for(int i = 0; i<size;i++)
	{
		int size_s = this->symbols.size();	
		if(std::find(symbols.begin(),symbols.end(),buffer[i]) == symbols.end())
		{
			MessageElement me(buffer[i],size);  
			symbols.push_back(me);
			for(int j = i+1; j<size; j++)
				if(buffer[i] == buffer[j])
					symbols[symbols.size()-1].IncreaseC();
		}
	}

	std::sort(symbols.begin(),symbols.end(),symbols[0]);
	for(int i = 0; i< symbols.size(); i++)
		cout<<symbols[i].Symbol()<<"    "<<symbols[i].Probability()<<endl;
	Haffman hf;
	hf.GetCodeFromTable(&symbols);


	FILE* rezFile = fopen("rezult.txt","w");
	
	

	fseek(file,SEEK_SET,0);
	size = len%BUFF_SIZE;
//	this->removeSpave(buffer);
	for(int i = 0;i<len/BUFF_SIZE;i++)
	{
		size = fread(buffer,1,BUFF_SIZE,file);
		if(size!=BUFF_SIZE)
			cout<<endl<<endl<<ferror(file)<<endl<<endl;
		//this->removeSpave(buffer);
		for(int j = 0; j<BUFF_SIZE;j++)
		{
			auto it = find(symbols.begin(),symbols.end(),buffer[j]);
			fwrite(it->Combination().data(),1,it->Combination().length(),rezFile);
		}
	}
	size = len%BUFF_SIZE;
	fread(buffer,1,len%BUFF_SIZE,file);
	for(int j = 0; j<size;j++)
	{

		auto it = find(symbols.begin(),symbols.end(),buffer[j]);
		fwrite(it->Combination().data(),1,it->Combination().length(),rezFile);
	}
	
	entropy();
	fclose(rezFile);
}

bool checkNewLine(char delim)
{
	return delim!='\n';
}

void FileWorker::removeSpave(char* str,bool (*check)(char delim))
{
	for(char* tStr = str; *tStr; tStr++)
	{
		if(check(*tStr))
			*str++ = *tStr;
	}
	*str=0;
}


void FileWorker::Decode()
{
	FILE* rezFile = fopen("rezult.txt","rb");
	FILE* rezFile1 = fopen("rezult1.txt","wb");
	int des = _fileno(rezFile);
	int len = _filelength(des);
	int size = 0;
	std::string comb;
	int loopSize = len;
	if(loopSize<BUFF_SIZE)
	{
		fread(buffer,1,BUFF_SIZE,rezFile);
		for(int j = 0; j<BUFF_SIZE;j++)
		{
			comb+=buffer[j];
			auto it = std::find(symbols.begin(),symbols.end(),comb);
			if(it!=symbols.end())
			{
				char p = it->Symbol();
				fwrite(&p,1,1,rezFile1);
				comb.clear();
			}
		}
	}
	else 
	{
		for(int i = 0;i<loopSize;i++)
		{
			size = fread(buffer,1,BUFF_SIZE,rezFile);
			this->removeSpave(buffer,checkNewLine);
			for(int j = 0; j<BUFF_SIZE;j++)
			{
				comb+=buffer[j];
				auto it = std::find(symbols.begin(),symbols.end(),comb);
				if(it!=symbols.end())
				{
					char p = it->Symbol();
					fwrite(&p,1,1,rezFile1);
					comb.clear();
				}
			}
			memset(buffer,0,BUFF_SIZE);
			comb.clear();

		}
	}
	fclose(rezFile);
	fclose(rezFile1);
}



void FileWorker::entropy()
{
	auto it = symbols.end();
	double sum = 0; 
	for(auto i = symbols.begin(); i!=it;i++)
		sum+= - i->Probability()*(log(i->Probability())/log(2));
	cout<<"Original entropy: "<<sum<<endl;
}