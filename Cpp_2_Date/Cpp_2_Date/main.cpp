#include <iostream>

class Date
{
	int _year;
	int _month;
	int _day;

public:
	//void SetDate();				// 생성자로
	void AddDay(int& inc);
	void AddMonth(int& inc);
	void AddYear(int& inc);

	int GetCurrentMonthDays(int& year, int& month);

	void ShowDate();

public:
	Date(int year, int month, int day)
		: _year(year)
		, _month(month)
		, _day(day)
	{ }
};

int main()
{
	Date* _date = new Date(2025, 5, 12);
	_date->ShowDate();

	int day = 0;

	std::cout << "몇일 후 : ";
	std::cin >> day;

	_date->AddDay(day);

	_date->ShowDate();

	delete _date;
	return 0;
}

void Date::AddDay(int& inc)
{
	_day += inc;
	while (true)
	{
		int current_month_days = GetCurrentMonthDays(_year, _month);
		if (_day <= current_month_days) break;
		_day -= current_month_days;
		int a = 1;
		AddMonth(a);
	}
}

void Date::AddMonth(int& inc)
{
	if ((_month + inc) <= 12)
	{
		_month += inc;
	}
	else
	{
		int a = (_month + inc) / 12;
		_month = (_month + inc) % 12;
		AddYear(a);
	}
}

void Date::AddYear(int& inc)
{
	_year += inc;
}

int Date::GetCurrentMonthDays(int& year, int& month)
{
	static int c_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (2 != month)
	{
		return c_month[month - 1];
	}
	else if (year % 4 == 0 && year % 100 != 0)
	{
		return 29;
	}
	else
	{
		return 28;
	}
}

void Date::ShowDate()
{
	std::cout << _year << "년 "
						<< _month << "월 "
						<< _day << "일" << std::endl;
}
