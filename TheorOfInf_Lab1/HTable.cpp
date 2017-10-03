#include "stdafx.h"


HTable::HTable (std::string value)
{
	std::vector<leaf*> values;
	for(auto i = value.begin(); i!=value.end();i++)
	{
		auto tmpL = new leaf;
		tmpL->left=tmpL->right = NULL;
		tmpL->value = *i;
		values.push_back(tmpL);
	}
	build(values);
	
		

}


void HTable::build(std::vector<leaf*> value)
{
	int fLen = value.size()-1;
	if(fLen == 0)
	{
		head = value[0];
		return;
	}
	std::vector<leaf*> tmpV;
	cout<<"NEXT ITTERATION"<<endl;
	for(int i = fLen; i>0 ; i-=2)
	{
		auto tmpL = new leaf;
		tmpL->right = value[i];
		tmpL->left  = value[i-1];
		std::string newValStr(value[i-1]->value+value[i]->value);
		cout<<newValStr<<endl;
		tmpL->value+=newValStr;
		tmpV.push_back(tmpL);
	}
	if((fLen+1) % 2 == 1 && (fLen+1) != 1)
		tmpV.push_back(value[0]);
	reverse(tmpV.begin(),tmpV.end());
	build(tmpV);

}


std::string HTable::Search(std::string value)
{
	std::string* rez = new std::string;

	try
	{
		if(head->left->value.find(value)!=string::npos)
		{
			(*rez)+='0';
			search(head->left,value,rez);
		}
		else 
		{
			(*rez)+='1';
			search(head->right,value,rez);
		}

	}
	catch(std::string* rez)
	{
		return *rez;
	}

}


void HTable::search(leaf* l,std::string value,std::string* rez)
{
	if(l->left == NULL && l->right ==NULL)
		throw(rez);

	if(l->left->value.find(value)!=string::npos)
	{
		(*rez)+='0';
		search(l->left,value,rez);
	}
	else 
	{
		(*rez)+='1';
		search(l->right,value,rez);
	}
}