#include "stdafx.h"
#include <io.h>
#pragma once

#define RNUMBER 3
#define MAX_POS_SIZE_STR 5


class badValue : public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Bad value exc";
	}
};


MessageElement::MessageElement(char s, int g):symbol(s),count(1),general_c(g)
{

}

char MessageElement::Symbol() 
{
	return symbol;
}

void MessageElement::IncreaseC()
{
	this->count++;
}

bool MessageElement::operator() (MessageElement& i,MessageElement& j)
{
	return i.Probability()>j.Probability();
}

double MessageElement::Probability()
{
	return  (double)count/(double)general_c;
}

bool MessageElement::operator==(char s) const
{
	if(symbol == s)
		return true;
	else 
		return false;
}

bool MessageElement::operator==(std::string s) const
{
	if(combination == s)
		return true;
	else 
		return false;
}

std::string& MessageElement::Combination()
{
	return this->combination;
}


int xor(int num1, int num2)
{
	if((num1 == 0 && num2 == 0) || (num1 == 1 && num2 == 1))
		return 0;
	else if((num1 == 0 && num2 == 1) || (num1 == 1 && num2 == 0))
		return 1;
	else 
		throw new badValue;
}



void GrayEncoder::getCode(const void* text)
{
	bytesArray.clear();
	int len = strlen((char*)text);
	for(int i = 0; i< len; i++)
	{
		bytesArray.push_back(std::bitset<BYTESIZE>(((unsigned char*)text)[i]));
		cout<<bytesArray[i].to_string()<<" ";
	}
	cout<<endl;
	int count = 0;
	cout<<"Encoded bytes by Gray's method: ";

	auto end = bytesArray.end();
	for(auto i =bytesArray.begin() ; i!=end;i++)
	{
		std::bitset<BYTESIZE> mask = *i;
		for(int j = BYTESIZE-1 ; j>0 ;j--)
		{
			mask[j-1] = i->at(j);
		}


		for(int j = BYTESIZE-1 ; j>=0 ;j--)
		{
			if(j == BYTESIZE-1)
			{
				continue;
			}
			else
			{
				try
				{
					i->at(j) = xor(i->at(j),mask[j]);
				}
				catch(badValue* e)
				{
					delete e;
					return;
				}
			}
		}
		cout<<i->to_string()<<" ";
	}
	cout<<endl<<"Encoded text by Gray's method: ";

	for(auto i = bytesArray.begin(); i!=end;i++)
	{
		cout<<(char)i->to_ulong();
	}
	cout<<endl;
}



void GrayEncoder::getString()
{
	int tmp;
	auto end = bytesArray.end();
	cout<<"Decoded text by Gray's method: ";
	for(auto i =bytesArray.begin() ; i!=end;i++)
	{
		for(int j = BYTESIZE-1; j>=0;j--)
		{
			if(j == BYTESIZE-1)
			{
				tmp = i->at(j);
			}
			else
			{
				try
				{
					i->at(j) = xor(i->at(j),tmp);
					tmp = i->at(j);
				}
				catch(badValue* e)
				{
					delete e;
					return;
				}
			}
		}
		cout<<(char)i->to_ulong();
	}
	cout<<endl;
}




void BCDEncoder::getCode(const void* text)
{
	
	int len = strlen((char*)text);
	int* tmpArr = new int[strlen((char*)text)];
	for(int i = 0; i<len;i++)
		tmpArr[i] = (unsigned char)((char*)text)[i];
	bytesArray.clear();
	int codeKoef [] = {8,4,2,1};


	cout<<"Encoded by BCD bytes: "<<endl;
	for(int i = 0; i<len; i++)
	{
		int tmpNumber;
		int count = 3;
		std::bitset<BCDSIZE> setBit;
		bytesArray.push_back(setBit);
		while(tmpArr[i]!=0)
		{
			tmpNumber = tmpArr[i]%10;
			for(int j = count, k = 0; k<4 ;j--,k++)
			{
				if(tmpNumber<codeKoef[k])
					bytesArray[i].set(j,0);
				else 
				{
					bytesArray[i].set(j,1);
					tmpNumber-=codeKoef[k];
				}
			}
			tmpArr[i]/=10;
			count+=4;
		}
		
		
		for(int j = 0; j<BCDSIZE; j++)
		{
			cout<<bytesArray[i].to_string()[j];
			/*if(j%4==3)
				cout<<" ";*/
		}
		cout<<endl;
	}
	delete tmpArr;

}

void BCDEncoder::getString()
{
	int len = bytesArray.size();
	int codeKoef [] = {8,4,2,1};
	cout<<"Decoded by BCD: ";
	for(int i = 0; i<len;i++)
	{
		int count = 0;
		int number = 0;
		for(int j = BCDSIZE-1; j>=0; j--)
		{
			number+=codeKoef[count++]*(int)bytesArray[i][j];
			if(count == 4)
			{
				number*=10;
				count=0;
			}
		}
		cout<<(char)(number/10);
	}
	cout<<endl;

}


void BergerEncoder::getCode(const void* text)
{
	bytesArray.clear();
	int len = strlen((char*)text);
	for(int i = 0; i< len; i++)
			bytesArray.push_back(std::bitset<8>(((unsigned char*)text)[i]));



	int amount = countOnes();
	int bytesAmount = floor(log(len*8)/log(2));
	

	this->sum = this->toSpecBinary(amount,bytesAmount);
	auto lenSum = sum.length();
	for(int i = 0; i<lenSum;i++)
	{
		if(sum[i] == '0')
			sum[i] = '1';
		else 
			sum[i] = '0';
	}
	auto end = bytesArray.end();
	cout<<"Encoded by Berger code: ";
	for(auto i = bytesArray.begin(); i<end ; i++)
		cout<<i->to_string()<<" ";
	cout<<sum;
	cout<<endl;
}


void BergerEncoder::getString()
{
	cout<<"Decoded by Berger's method: ";
	auto end = bytesArray.end();
	for(auto i = bytesArray.begin(); i<end ; i++)
		cout<<i->to_string()<<" ";

	cout<<endl<<"Decoded  text by Berger's method: ";
	for(auto i = bytesArray.begin(); i<end ; i++)
		cout<<(char)i->to_ulong();

}

int BergerEncoder::countOnes()
{
	int count = 0;
	auto end = bytesArray.end();
	for(auto i = bytesArray.begin(); i<end ; i++)
	{
		for(int j = 0; j<BYTESIZE ; j++)
			if(i->at(j) == 1)
				count++;
	}
	return count;
}


std::string BergerEncoder::toSpecBinary(int number, int maxExp)
{
	std::string tmpRez;
	std::string tmpZeros;
	int count = 0;
	while(number!=0)	
	{
		int tmpNum = number / 2;
		tmpRez += (number - tmpNum*2)+ '0';
		number/=2;
		count++;
	}
	std::reverse(tmpRez.begin(),tmpRez.end());
	for(int i = 0;i<maxExp - (count-1);i++)
		tmpZeros+='0';
	tmpZeros+=tmpRez;
	
	return tmpZeros;
}





void ModQCheckingEncoder::getCode(const void* text)
{
	char* Tex = new char[CHAR_COUNT];
	int len = strlen((char*)text);
	int* tmpArr = new int[strlen((char*)text)];
	for(int i = 0; i<len;i++)
		tmpArr[i] = (int)((unsigned char*)text)[i];

	cout<<endl<<"Encoded by ModQCheckingEncoder: ";
	for(int i = 0; i<len; i++)
	{
		int num = Qq-(sumNumber(tmpArr[i])%Qq);
		if(num == Qq)
			num = 0;
		sprintf(Tex,"%d%d",tmpArr[i],num);
		this->buffer.push_back(std::string (Tex));
		cout<<this->buffer[i]<<" ";
	}
	cout<<endl;
	delete[] Tex;
	delete[] tmpArr;
}


int ModQCheckingEncoder::sumNumber(int number)
{
	int sum = 0;
	while(number!=0)
	{
		sum+= number%10;
		number/=10;
	}
	return sum;
}


void ModQCheckingEncoder::getString()
{
	auto len = buffer.end();
	cout<<"Decoded by ModQCheckingEncoder: ";
	for(auto i = buffer.begin(); i<len ; i++)
	{
		(*i).erase((*i).end()-1);
		cout<<(*i) <<" ";
	}
	cout<<endl;
}


void RepeatedNumberEncoder::getCode(const void* text)
{
	char Tex [CHAR_COUNT];
	int len = strlen((char*)text);
	int* tmpArr = new int[strlen((char*)text)];
	for(int i = 0; i<len;i++)
		tmpArr[i] = (int)((unsigned char*)text)[i];
	
	cout<<"Encoded by RepeatedNumberEncoder: ";
	for(int i = 0; i<len; i++)
	{
		sprintf(Tex,"%d%d",tmpArr[i],tmpArr[i]);
		this->buffer.push_back(std::string (Tex));
		cout<<this->buffer[i]<<" ";
	}
	
	delete[] tmpArr;
}

void RepeatedNumberEncoder::getString()
{
	auto len = buffer.size();
	cout<<endl<<"Decoded by ModQCheckingEncoder: ";
	for(auto i = 0 ; i<len ; i++)
	{
		std::string tmp(buffer[i].begin(), buffer[i].begin()+buffer[i].length()/2);
		buffer[i].clear();
		buffer[i] = tmp;
		cout<<buffer[i]<<" ";
	}
}

void IterativeEndcoder::getCode(const void* text)
{
	int len = strlen((char*)text);
	int* tmpArr = new int[strlen((char*)text)];
	for(int i = 0; i<len;i++)
		tmpArr[i] = (int)((unsigned char*)text)[i];
	std::string tmpFullStr;
	char Tex [CHAR_COUNT];
	for(int i = 0; i<len;i++)
	{
		sprintf(Tex,"%d",tmpArr[i]);
		tmpFullStr+=Tex;
	}
	int order = ceil(sqrt(tmpFullStr.size()));
	int generCount = 0;
	for(int i = 0; i<order;i++)
	{
		std::string newNode;
		lines.push_back(newNode);
		for(int j = 0; j<order;j++)
		{
			if(generCount>=tmpFullStr.size())
				this->lines[i]+='0';
			else 
				this->lines[i]+=tmpFullStr[generCount++];
		}
	}


	cout<<endl<<"Message matrix which will be used to form Control Sum(Iterative Encoder): "<<endl;
	auto end = lines.end();
	for(auto i = lines.begin(); i<end;i++)
		cout<<(*i)<<endl;

	for(auto i = 0 ; i< order ;i++)
	{
		int sumVer = 0, sumHor = 0;
		for(int j = 0; j<order; j++)
		{
			sumHor+= lines[i][j] - '0';
			sumVer+= lines[j][i] - '0';
		}
		int rez = Qq - sumHor%Qq;
		if(rez==Qq)
			rez=0;
		sprintf(Tex,"%d",rez);
		codeColumm+=Tex;
		rez = Qq - sumVer%Qq;
		if(rez==Qq)
			rez=0;
		sprintf(Tex,"%d",rez);
		codeLine+=Tex;
	}
	cout<<"Coded Message Matrix: "<<endl;
	generCount=0;
	for(auto i = lines.begin(); i<end;i++)
		cout<<(*i)<<" "<<codeColumm[generCount++]<<endl;
	cout<<endl;

	int size = codeColumm.size();
	int sum = 0;
	for(int i = 0; i<size; i++)
	{
		sum+=codeColumm[i]-'0';
	}
	diagElement = Qq - sum%Qq;
	if(diagElement = Qq)
		diagElement = 0;

	cout<<codeLine<<" "<<diagElement<<endl;
}


void IterativeEndcoder::getString()
{
	cout<<"Checking: "<<endl;
	int order = codeColumm.size();

	std::string tmpLine;

	char Tex[CHAR_COUNT]; 
	for(auto i = 0 ; i< order ;i++)
	{
		int sumVer = 0, sumHor = 0;
		for(int j = 0; j<order; j++)
		{
			sumHor+= lines[i][j] - '0';
			sumVer+= lines[j][i] - '0';
		}
		cout<<lines[i]<<" "<<codeColumm[i]<<" ";

		sumHor+=codeColumm[i]-'0';
		sumVer+=codeLine[i]-'0';

		int rez = Qq - sumHor%Qq;
		if(rez==Qq)
			rez=0;
		sprintf(Tex,"%d",rez);
		cout<<rez<<endl;
		rez = Qq - sumVer%Qq;
		if(rez==Qq)
			rez=0;
		sprintf(Tex,"%d",rez);
		tmpLine+=rez+'0';
	}
	int tmpSum=0,rez=0;
	for(int i = 0;i<tmpLine.size();i++)
		tmpSum+=tmpLine[i]-'0';
	rez = Qq - tmpSum%Qq;
	if(rez == Qq)
		rez=0;
	cout<<codeLine<<" "<<diagElement<<endl;
	cout<<endl<<tmpLine<<" "<<rez<<endl;
	

}


void ElaesEndcoder::getCode(const void* text)
{
	int len = strlen((char*)text);
	int* tmpArr = new int[strlen((char*)text)];
	for(int i = 0; i<len;i++)
		tmpArr[i] = (int)((unsigned char*)text)[i];
	std::string tmpFullStr;
	
	for(int i = 0; i<len;i++)
	{
		std::bitset<8> tmpByte(tmpArr[i]);
		tmpFullStr+=tmpByte.to_string();
	}
	int order = ceil(sqrt(tmpFullStr.size()));
	int generCount = 0;
	for(int i = 0; i<order;i++)
	{
		std::string newNode;
		lines.push_back(newNode);
		for(int j = 0; j<order;j++)
		{
			if(generCount>=tmpFullStr.size())
				this->lines[i]+='0';
			else 
				this->lines[i]+=tmpFullStr[generCount++];
		}
	}

	char Tex[CHAR_COUNT];
	cout<<endl<<"Message matrix which will be used to form Control Sum(Elaes Encoder): "<<endl;
	auto end = lines.end();
	for(auto i = lines.begin(); i<end;i++)
		cout<<(*i)<<endl;

	for(auto i = 0 ; i< order ;i++)
	{
		int sumVer = 0, sumHor = 0;
		for(int j = 0; j<order; j++)
		{
			sumHor+= lines[i][j] - '0';
			sumVer+= lines[j][i] - '0';
		}
		int rez = sumHor%2;
		if(rez==2)
			rez=0;
		sprintf(Tex,"%d",rez);
		codeColumm+=Tex;
		rez = sumVer%2;
		if(rez==2)
			rez=0;
		sprintf(Tex,"%d",rez);
		codeLine+=Tex;
	}
	cout<<"Coded Message Matrix: "<<endl;
	generCount=0;
	for(auto i = lines.begin(); i<end;i++)
		cout<<(*i)<<" "<<codeColumm[generCount++]<<endl;
	cout<<endl;
	cout<<this->codeLine<<endl;
}

void ElaesEndcoder::getString()
{
	cout<<"Checking: "<<endl;
	int order = codeColumm.size();

	std::string tmpLine;

	char Tex[CHAR_COUNT]; 
	for(auto i = 0 ; i< order ;i++)
	{
		int sumVer = 0, sumHor = 0;
		for(int j = 0; j<order; j++)
		{
			sumHor+= lines[i][j] - '0';
			sumVer+= lines[j][i] - '0';
		}
		cout<<lines[i]<<" "<<codeColumm[i]<<" ";

		sumHor+=codeColumm[i]-'0';
		sumVer+=codeLine[i]-'0';

		int rez = sumHor%2;
		if(rez==2)
			rez=0;
		sprintf(Tex,"%d",rez);
		cout<<rez<<endl;
		rez = sumVer%2;
		if(rez==2)
			rez=0;
		tmpLine+=rez+'0';

	}
	cout<<endl<<codeLine<<endl;
	cout<<tmpLine<<" "<<endl;
}


void replaceAll(string &s,const string &search,const string &replace ) 
{
	int pos = 0;
	while(true)
	{
        pos = s.find(search,pos);
        if(pos == string::npos) 
			break;
        s.erase(pos,search.length());
        s.insert(pos,replace);
    }
}
void ShennonFano::getCode(const void* text)
{
	char* tex = (char*)text;
	int size = strlen(tex);

	for(int i = 0; i<size;i++)
	{
		int size_s = this->symbols.size();	
		if(std::find(symbols.begin(),symbols.end(),tex[i]) == symbols.end())
		{
			MessageElement me(tex[i],size);

			symbols.push_back(me);
			for(int j = i+1; j<size; j++)
				if(tex[i] == tex[j])
					symbols[symbols.size()-1].IncreaseC();
		}

	}
	std::sort(symbols.begin(),symbols.end(),symbols[0]);
	devideIntoTwo(0,symbols.size()-1);
	for(int i = 0; i<symbols.size(); i++)
	{
		cout<<setw(2)<<symbols[i].Symbol()<<" "<<symbols[i].Probability()<<" "<<symbols[i].Combination()<<endl;
	}
	
	for(int i = 0; i<size;i++)
	{
		auto it = std::find(symbols.begin(),symbols.end(),tex[i]);
		coded_txt+=it->Combination();
	}
	cout<<coded_txt;
}


void ShennonFano::devideIntoTwo(int begin, int end)
{
	int middle = begin;
	
	if(end - begin == 1)
	{
		symbols[begin].Combination()+='0';
	    symbols[end].Combination()+='1';
		return;
	}
	else if(begin - end == 0)
	{
        //symbols[begin].Combination()+='0';
		return;
	}
	
	
	double p1(symbols[begin].Probability()),p2(0), checkSum(0);
	while(checkSum<abs(p2-p1))
	{
		checkSum = abs(p2-p1);
		p1=p2=0;
		++middle;
		for(int i = begin; i<middle;i++)
			p1+=symbols[i].Probability();
		for(int i = middle; i<=end;i++)
			p2+=symbols[i].Probability();
		
	}
	if((checkSum == abs(p2-p1) || checkSum == p1 && p1<=0.5) && middle+1!=end)
		middle++;
  
	for(int i = begin; i<middle;i++)
		symbols[i].Combination()+='0';
	for(int i = middle; i<=end;i++)
		symbols[i].Combination()+='1';
	
	devideIntoTwo(begin,middle-1);
	devideIntoTwo(middle,end);
	

	
}



void ShennonFano::getString()
{
	std::string comb;
	std::string rez;
	auto i = coded_txt.begin();
	while(i!=coded_txt.end())
	{
		comb+=(*i);
		auto it = std::find(symbols.begin(),symbols.end(),comb);
		if(it!=symbols.end())
		{
			rez += it->Symbol();
			comb.clear();
			i=coded_txt.erase(coded_txt.begin(),i+1);
		}
		else 
			i++;
	}
	std::cout<<rez;
}

void ShennonFano::GetCodeFromTable(std::vector<MessageElement>* table)
{
}


void Haffman::getCode(const void* txt)
{
	char* tex = (char*)txt;
	int size = strlen(tex);

	for(int i = 0; i<size;i++)
	{
		int size_s = this->symbols.size();	
		if(std::find(symbols.begin(),symbols.end(),tex[i]) == symbols.end())
		{
			MessageElement me(tex[i],size);  
			symbols.push_back(me);
			for(int j = i+1; j<size; j++)
				if(tex[i] == tex[j])
					symbols[symbols.size()-1].IncreaseC();
		}
	}
	std::sort(symbols.begin(),symbols.end(),symbols[0]);
	std::string fullProbString;
	for(auto i = symbols.begin(); i!=symbols.end();i++)
	{
		fullProbString+=i->Symbol();
	}
	HTable ht (fullProbString);
	
	auto end = symbols.end();
	for(auto i = symbols.begin(); i!=end;i++)
	{
		std::string value(ht.Search(std::string(1,i->Symbol())));
		i->Combination() = value;
		cout<<i->Symbol()<<"  "<<value<<endl;
	}

	for(int i = 0; i<size;i++)
	{
		auto it = std::find(symbols.begin(),symbols.end(),tex[i]);
		coded_txt+=it->Combination();
	}
	cout<<endl<<coded_txt<<endl;


}
void Haffman::getString()
{
	std::string comb;
	std::string rez;
	auto i = coded_txt.begin();
	while(i!=coded_txt.end())
	{
		comb+=(*i);
		auto it = std::find(symbols.begin(),symbols.end(),comb);
		if(it!=symbols.end())
		{
			rez += it->Symbol();
			comb.clear();
			i=coded_txt.erase(coded_txt.begin(),i+1);
		}
		else 
			i++;
	}
	std::cout<<rez;
}


void Haffman::GetCodeFromTable(std::vector<MessageElement>* table)
{
	std::sort(table->begin(),table->end(),(*table)[0]);
	std::string fullProbString;
	for(auto i = table->begin(); i!=table->end();i++)
	{
		fullProbString+=i->Symbol();
	}
	HTable ht (fullProbString);
	auto end = table->end();
	for(auto i = table->begin(); i!=end;i++)
	{
		std::string value(ht.Search(std::string(1,i->Symbol())));
		i->Combination() = value;
		cout<<i->Symbol()<<"  "<<value<<endl;
	}

}