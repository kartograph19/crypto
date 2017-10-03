#include "stdafx.h"

#pragma once 
#define BYTESIZE 8
#define BCDSIZE 12
#define CHAR_COUNT 7
#define Qq 10

#include <algorithm>


class MessageElement 
{
	char symbol;
	int count;
	int general_c;
	std::string combination;
public:
	MessageElement(char s, int g);
	void IncreaseC();
	char Symbol();
	double Probability();
	bool operator ==(char val) const;
	bool operator ==(std::string val) const;
	bool operator() (MessageElement& i, MessageElement& j);
	std::string& Combination();
};


class IEncoder
{
public:
	void virtual getCode(const void* text) = 0;
	void virtual getString() = 0;
};


class GrayEncoder: public IEncoder
{
	std::vector<std::bitset<BYTESIZE>> bytesArray; 
public:
	void virtual getCode(const void* text);
	void virtual getString();
};


class BCDEncoder: public IEncoder
{
	std::vector<std::bitset<BCDSIZE>> bytesArray;
public:
	void virtual getCode(const void* text);
	void virtual getString();
};


class BergerEncoder: public IEncoder
{
	std::vector<std::bitset<BYTESIZE>> bytesArray;
	std::string sum;
	int countOnes();
	std::string toSpecBinary(int number, int maxExp);
public:
	void virtual getCode(const void* text);
	void virtual getString();
};


class ModQCheckingEncoder : public IEncoder
{
	std::vector<std::string> buffer;
	//const static int Q = 10;
	int sumNumber(int num);
	public:
	void virtual getCode(const void* text);
	void virtual getString();
};


class RepeatedNumberEncoder: public IEncoder
{
	std::vector<std::string> buffer;
	public:
	void virtual getCode(const void* text);
	void virtual getString();
};


class IterativeEndcoder : public IEncoder
{
	std::vector<std::string> lines;
	std::string codeColumm;
	std::string codeLine;
	int diagElement;
public:
	void virtual getCode(const void* text);
	void virtual getString();
};


class ElaesEndcoder : public IEncoder
{
	std::vector<std::string> lines;
	std::string codeColumm;
	std::string codeLine;
public:
	void virtual getCode(const void* text);
	void virtual getString();
};

class ShennonFano : public IEncoder
{
	void devideIntoTwo(int begin,int end);
	std::vector<MessageElement> symbols;
	std::string coded_txt;
public:
	void virtual getCode(const void* text);
	void GetCodeFromTable(std::vector<MessageElement>*);
	void virtual getString();

};


class Haffman: public IEncoder
{
	std::vector<MessageElement> symbols;
	std::string coded_txt;;
public:
	void virtual getCode(const void* text);
	void GetCodeFromTable(std::vector<MessageElement>*);
	void virtual getString();
};












