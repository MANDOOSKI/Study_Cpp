#pragma once
#include <cstring>
#include <iostream>

class g_character
{
	static int population;
	const int supply;
	wchar_t* name;
	int hp;
	int coord_x;
	int coord_y;
	const int damage;
	bool is_dead;

public:
	int attack() { return damage; }
	void be_attack(const int& _damage);
	void move(const int& x, const int& y);
	void show_state();
	static void show_population();

public:
	g_character()
		: name(nullptr)
		, hp(0)
		, coord_x(0)
		, coord_y(0)
		, damage(0)
		, supply(0)
		, is_dead(true)
	{ }
	g_character(const wchar_t* c_name, int hp, int x, int y, int c_damage, int c_supply)
		: hp(hp)
		, coord_x(x)
		, coord_y(y)
		, damage(c_damage)
		, supply(c_supply)
		, is_dead(false)
	{
		if (nullptr != c_name)
		{
			size_t len = std::wcslen(c_name);
			name = new wchar_t[len + 1];
			wcscpy_s(name, len + 1, c_name);
		}
		else
		{
			name = nullptr;
		}
		population += supply;
	}
	g_character(const g_character& _other)
		: hp(_other.hp)
		, coord_x(_other.coord_x + 1)
		, coord_y(_other.coord_y)
		, damage(_other.damage)
		, supply(_other.supply)
		, is_dead(false)
	{
		if (_other.name)
		{
			size_t len = std::wcslen(_other.name);
			name = new wchar_t[len + 1];
			wcscpy_s(name, len + 1, _other.name);
		}
		else
		{
			name = nullptr;
		}
		population += supply;
	}
	~g_character()
	{
		delete[] name;
	}
};

