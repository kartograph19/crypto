#include "stdafx.h"

#pragma once 

class HTable
{
	struct leaf
	{
		std::string value;
		leaf* left;
		leaf* right;
		leaf* top;
	};
	leaf* head; 
	void search(leaf* l,std::string value,std::string* rez);
	void build(std::vector<leaf*> value);
public:
	HTable (std::string value);
	std::string Search(std::string value);
};