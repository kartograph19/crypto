#include "stdafx.h"
const std::string ICrypto::alphabet = "abcdefghijklmnopqrstuvwxyz ";

std::string CesarCode::Encode(const void* text, void* key)
{
	std::string closed_alphabet;
	for(int i = 0; i<alphabet.length(); i++)
	{
		int y =(i + *((int*)key)) % alphabet.length();
		closed_alphabet += alphabet[y];
	}
	int len = strlen((char*)text);

	std::string coded_text;
	for(int i = 0; i<len; i++)
	{
		bool found = false; 
		for(int j = 0; j<alphabet.length(); j++)
		{
			if( tolower(((char*)text)[i]) == alphabet[j])
			{
				coded_text+= closed_alphabet[j];
				found = true;
			}
		}
		if(!found)
			coded_text+=((char*)text)[i];
	}
	return coded_text;
}

void CesarCode::Decode(const void* text, void* key)
{
	std::string closed_alphabet;
	for(int i = 0; i<alphabet.length(); i++)
	{
		int y =(i + *((int*)key)) % alphabet.length();
		closed_alphabet += alphabet[y];
	}
	int len = strlen((char*)text);

	std::string decoded_text;
	for(int i = 0; i<len; i++)
	{
		bool found = false; 
		for(int j = 0; j<alphabet.length(); j++)
		{
			if( tolower(((char*)text)[i]) == closed_alphabet[j])
			{
				decoded_text+= alphabet[j];
				found = true;
			}
		}
		if(!found)
			decoded_text+=((char*)text)[i];
	}
	cout<<decoded_text;


}



std::string Tritemius::Encode(const void* text, void* key)
{
	int len = strlen((char*)text);

	std::string coded_text;
	for(int i = 0; i<len; i++)
	{
		int num_in_alph = -1; 
		for(int j = 0; j<alphabet.length(); j++)
		{
			if( tolower(((char*)text)[i]) == alphabet[j])
			{
				num_in_alph = j;
			}
		}
		if(num_in_alph!=-1)
			coded_text+= alphabet[(this->change_func(i) + num_in_alph)% alphabet.length()];
		else
			coded_text+= ((char*)text)[i];
	}
	return coded_text;
}

void Tritemius::Decode(const void* text, void* key)
{
	int len = strlen((char*)text);

	std::string decoded_text;
	for(int i = 0; i<len; i++)
	{
		int num_in_alph = -1; 
		for(int j = 0; j<alphabet.length(); j++)
		{
			if( ((char*)text)[i] == alphabet[j])
			{
				num_in_alph = j;
			}
		}
		if(num_in_alph!=-1)
		{
			int ord_num = (num_in_alph-this->change_func(i));
			if(ord_num< 0) 
				while(ord_num<0)
					ord_num += alphabet.length();
			decoded_text+= alphabet[ord_num % alphabet.length()];
		}
		else
			decoded_text+= ((char*)text)[i];
	}
	cout<<decoded_text<<endl;
}

int Tritemius::change_func(int num)
{
	return 2 * pow(num,2) + 5* num + 2;
}

std::string Vizhener::Encode(const void* text, void* key)
{
	int len = strlen((char*)text);
	int len_key = strlen((char*)key);
	std::string full_key;
	std::string coded_text;
	for(int i = 0; i<len/len_key; i++)
		full_key+=(char*)key;
	for(int i = 0; i<len % len_key; i++)
		full_key+=((char*)key)[i];
	
	for(int i = 0; i< len; i++)
	{
		const char* ptr_to_found_text = strchr(alphabet.c_str(),tolower(((char*)text)[i]));
		const char* ptr_to_found_alph = strchr(alphabet.c_str(),tolower(full_key[i]));

		int text_indx = ptr_to_found_text - alphabet.c_str();
		int alph_indx = ptr_to_found_alph - alphabet.c_str();
		int num =(text_indx + alph_indx) % alphabet.length();
		coded_text+= alphabet[num];
	}
	return coded_text;
}

void Vizhener::Decode(const void* text, void* key)
{
	int len = strlen((char*)text);
	int len_key = strlen((char*)key);
	std::string full_key;
	std::string decoded_text;
	for(int i = 0; i<len/len_key; i++)
		full_key+=(char*)key;
	for(int i = 0; i<len % len_key; i++)
		full_key+=((char*)key)[i];
	
	for(int i = 0; i< len; i++)
	{
		const char* ptr_to_found_text = strchr(alphabet.c_str(),((char*)text)[i]);
		const char* ptr_to_found_alph = strchr(alphabet.c_str(),full_key[i]);

		int text_indx = ptr_to_found_text - alphabet.c_str();
		int alph_indx = ptr_to_found_alph - alphabet.c_str();
		int num =(text_indx - alph_indx + alphabet.length()) % alphabet.length();
		decoded_text+= alphabet[num];
	}
	cout<<decoded_text;
}