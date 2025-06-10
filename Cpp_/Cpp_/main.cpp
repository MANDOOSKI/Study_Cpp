#include <iostream>

/*
- 문자(char)로 부터의 문자열 생성, C 문자열 (char *)로 부터의 생성
- 문자열 길이를 구하는 함수
- 문자열 뒤에 다른 문자열 붙이기
- 문자열 내에 포함되어 있는 문자열 구하기
- 문자열이 같은지 비교
- 문자열 크기 비교(사전 순)
*/

// -문자(char)로 부터의 문자열 생성, C 문자열(char*)로 부터의 생성
class _String
{
	char* str;

public:
	int strLen(const char* s);
	void strCat(const char* s);
	int find(const char* target);
	bool same(const char* target);

public:
	_String(char c)
		: str(new char[2])
	{
		str[0] = c;
		str[1] = '\0';
	}
	_String(const char* s)
	{
		if (s)
		{
			int len = strLen(s);
			str = new char[len + 1];
			for (int i = 0; i < len; ++i)
			{
				str[i] = s[i];
			}
			str[len] = '\0';
		}
		else
		{
			str = nullptr;
		}
	}
};

int main()
{
	// -문자(char)로 부터의 문자열 생성, C 문자열(char*)로 부터의 생성

	// - 문자열 길이를 구하는 함수
	
	// - 문자열 뒤에 다른 문자열 붙이기

	_String s = _String("Hello");
	std::cout << s.find("llo") << std::endl;
	std::cout << s.same("Hello") << std::endl;
	return 0;
}

// -문자열 길이를 구하는 함수
int _String::strLen(const char* s)
{
	if (s)
	{
		int len = 0;
		while (*s)
		{
			++s;
			++len;
		}
		return len;
	}
	return 0;
}

// - 문자열 뒤에 다른 문자열 붙이기
void _String::strCat(const char* s)
{
	if (!s) return;

	int len1 = strLen(str);
	int len2 = strLen(s);

	char* newString = new char[len1 + len2 + 1];

	for (int i = 0; i < len1; ++i)
	{
		newString[i] = str[i];
	}

	for (int i = 0; i < len2; ++i)
	{
		newString[len1 + i] = s[i];
	}
	newString[len1 + len2] = '\0';

	delete[] str;
	str = newString;
}

// - 문자열 내에 포함되어 있는 문자열 구하기
int _String::find(const char* target)
{
	if (!str || !target) return -1;

	int len1 = strLen(str);
	int len2 = strLen(target);

	if (len2 == 0) return 0;
	if (len1 < len2) return -1;

	for (int i = 0; i <= len1 - len2; ++i)
	{
		bool match = true;
		for (int j = 0; j < len2; ++j)
		{
			if (str[i + j] != target[j])
			{
				match = false;
				break;
			}
		}
		if (match)
		{
			return i;
		}
	}
	return -1;
}

// - 문자열이 같은지 비교
bool _String::same(const char* target)
{
	if (!str || !target) return false;
	int len1 = strLen(str);
	int len2 = strLen(target);

	if (len1 != len2) return false;

	for (int i = 0; i < len1; ++i)
	{
		if (str[i] != target[i])
		{
			return false;
		}
	}
	return true;
}
