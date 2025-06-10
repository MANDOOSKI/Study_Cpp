#include"header1.h"
#include"header2.h"

// namespace : 이름공간
//	- 함수, 객체 등이 정의된 이름 공간
//	- 어디 소속인지 지정해 주는것과 같음

//using header1::foo;						// header1이란 이름공간 안에있는 foo를 사용하겠다.
//using namespace header1;			// 이런식으로 사용을 해도 된다.
int main()
{
	//header1::foo();							// using 사용시 (using header1::foo; using namespace header1;) 작성시 header1::을 작성 안해도 된다.

	return 0;
}