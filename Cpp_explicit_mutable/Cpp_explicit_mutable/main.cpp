#include "MyString.h"

void DoSomethingWithString(MyString s)
{

}

int main()
{
	MyString a = "abc";
	MyString b = a;
	MyString c = 5;					// �̰� �ȵ� explicit Ű���尡 �ۼ��ؼ� MyString c(5); �̷��� �ؾ���
	return 0;
}