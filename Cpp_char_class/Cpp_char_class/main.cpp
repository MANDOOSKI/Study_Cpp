#include "string.h"

int main()
{
	string a('a', 5);
	string b(a);
	string c('s', 1);
	string d("abcde");
	a.add_string(c);

	return 0;
}