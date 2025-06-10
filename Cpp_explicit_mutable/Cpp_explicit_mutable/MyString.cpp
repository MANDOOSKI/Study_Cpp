#include "MyString.h"
#include <iostream>
#include <cstring>x

MyString::MyString()
	: string_length(0)
	, string_capacity(2)
	, string_content(new char[2])
{
	string_content[0] = '\0';
}

explicit MyString::MyString(int capacity)
	: string_length(0)
	, string_capacity(capacity)
	, string_content(new char[capacity])
{
	string_content[0] = '\n';
}

MyString::MyString(char c)
	: string_length(1)
	, string_capacity(2)
	, string_content(new char[2])
{
	string_content[0] = c;
	string_content[1] = '\0';
}

MyString::MyString(const char* str)
	: string_length(std::strlen(str))
	, string_capacity(string_length + 1)
	, string_content(new char[string_capacity])
{
	strcpy_s(string_content, string_capacity, str);

	/*
	for (int i = 0; i < string_length; ++i)
	{
		string_content[i] = str[i];
	}
	string_content[string_length] = '\0';
	*/
}

MyString::MyString(const MyString& str)
	: string_length(str.string_length)
	, string_capacity(str.string_capacity)
	, string_content(new char[string_capacity])
{
	strcpy_s(string_content, string_capacity, str.string_content);

	/*
	for (int i = 0; i < string_length; ++i)
	{
		string_content[i] = str.string_content[i];
	}
	string_content[string_length] = '\0';
	*/
}

MyString::~MyString()
{
	delete[] string_content;
}
