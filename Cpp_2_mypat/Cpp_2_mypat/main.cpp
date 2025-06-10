#include <iostream>

class Data
{
	int year_;
	int month_;
	int day_;

public :
	void SetData(int year, int month, int date);
	void AddDay(int inc);
	void AddMonth(int inc);
	void AddYear(int inc);

	void ShowDate();
};

int main()
{

	return 0;
}