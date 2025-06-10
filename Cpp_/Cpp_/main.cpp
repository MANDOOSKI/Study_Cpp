#include <iostream>

/*
- ����(char)�� ������ ���ڿ� ����, C ���ڿ� (char *)�� ������ ����
- ���ڿ� ���̸� ���ϴ� �Լ�
- ���ڿ� �ڿ� �ٸ� ���ڿ� ���̱�
- ���ڿ� ���� ���ԵǾ� �ִ� ���ڿ� ���ϱ�
- ���ڿ��� ������ ��
- ���ڿ� ũ�� ��(���� ��)
*/

// -����(char)�� ������ ���ڿ� ����, C ���ڿ�(char*)�� ������ ����
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
	// -����(char)�� ������ ���ڿ� ����, C ���ڿ�(char*)�� ������ ����

	// - ���ڿ� ���̸� ���ϴ� �Լ�
	
	// - ���ڿ� �ڿ� �ٸ� ���ڿ� ���̱�

	_String s = _String("Hello");
	std::cout << s.find("llo") << std::endl;
	std::cout << s.same("Hello") << std::endl;
	return 0;
}

// -���ڿ� ���̸� ���ϴ� �Լ�
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

// - ���ڿ� �ڿ� �ٸ� ���ڿ� ���̱�
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

// - ���ڿ� ���� ���ԵǾ� �ִ� ���ڿ� ���ϱ�
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

// - ���ڿ��� ������ ��
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
