#pragma once
class MyString
{
	int string_length;
	int string_capacity;
	char* string_content;

public:
	MyString();
	explicit MyString(int capacity);
	MyString(char c);
	MyString(const char* str);
	MyString(const MyString& str);

public:
	int length() const { return string_length; }

public:
	~MyString();
};

