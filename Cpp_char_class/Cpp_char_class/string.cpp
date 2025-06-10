#include "string.h"

string::string(char c, int n)
	: str(new char[n + 1])
	, len(n)
{
	for (int i = 0; i < len; ++i)
	{
		str[i] = c;
	}
	str[len] = '\0';
}

string::string(const char* s)
	: len(std::strlen(s))
	, str(new char[len + 1])
{
	strcpy_s(str, len + 1, s);
}

string::string(const string& s)
	: len(s.len)
	, str(new char[len + 1])
{
	strcpy_s(str, len + 1, s.str);
}

string::~string()
{
	delete[] str;
	len = 0;
}

void string::add_string(const string& s)
{
	len += s.len;
	char* new_str = new char[len + 1];
	strcpy_s(new_str, len + 1, str);
	strcat_s(new_str, len + 1, s.str);
	delete[] str;
	str = new_str;
}

void string::copy_string(const string& s)
{
	len = s.len;
	char* new_str = new char[len + 1];
	strcpy_s(new_str, len + 1, s.str);
	delete[] str;
	str = new_str;
}

int string::strlen()
{
	return len;
}
