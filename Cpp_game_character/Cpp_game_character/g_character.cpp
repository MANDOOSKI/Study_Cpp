#include "g_character.h"

int g_character::population = 0;

void g_character::be_attack(const int& _damage)
{
	
}

void g_character::move(const int& x, const int& y)
{
	coord_x = x;
	coord_y = y;
}

void g_character::show_state()
{
	std::wcout << name << "'s state" << std::endl;
	std::cout << "hp : " << hp << std::endl;
	std::cout << "��ġ : (" << coord_x << ", " << coord_y << ")" << std::endl;
	std::cout << "�������� : " << !is_dead << std::endl;
}

void g_character::show_population()
{
	std::cout << "���� �α� : " << population << std::endl;
}
