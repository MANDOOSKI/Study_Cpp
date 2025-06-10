#include "g_character.h"

int main()
{
	std::locale::global(std::locale(""));       // 전역 로케일 설정
	std::wcout.imbue(std::locale(""));          // wcout에도 로케일 적용
	
	g_character marine(L"마린", 50, 30, 40, 5, 1);
	marine.show_state();
	g_character::show_population();
	g_character marine2(L"마린", 50, 30, 40, 5, 1);
	marine2.show_state();
	g_character::show_population();
	g_character marine3(L"마린", 50, 30, 40, 5, 1);
	marine3.show_state();
	g_character::show_population();
	g_character marine4(L"마린", 50, 30, 40, 5, 1);
	marine4.show_state();
	g_character::show_population();
	g_character marine5(L"마린", 50, 30, 40, 5, 1);
	marine5.show_state();
	g_character::show_population();

	



	return 0;
}