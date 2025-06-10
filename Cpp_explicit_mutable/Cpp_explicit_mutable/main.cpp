#include "MyString.h"

void DoSomethingWithString(MyString s)
{

}

int main()
{
	MyString a = "abc";
	MyString b = a;
	MyString c = 5;					// 이건 안됨 explicit 키워드가 작성해서 MyString c(5); 이렇게 해야함
	return 0;
}