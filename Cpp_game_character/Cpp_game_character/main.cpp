#include "g_character.h"

int main()
{
	std::locale::global(std::locale(""));       // ���� ������ ����
	std::wcout.imbue(std::locale(""));          // wcout���� ������ ����
	
	g_character marine(L"����", 50, 30, 40, 5, 1);
	marine.show_state();
	g_character::show_population();
	g_character marine2(L"����", 50, 30, 40, 5, 1);
	marine2.show_state();
	g_character::show_population();
	g_character marine3(L"����", 50, 30, 40, 5, 1);
	marine3.show_state();
	g_character::show_population();
	g_character marine4(L"����", 50, 30, 40, 5, 1);
	marine4.show_state();
	g_character::show_population();
	g_character marine5(L"����", 50, 30, 40, 5, 1);
	marine5.show_state();
	g_character::show_population();

	



	return 0;
}