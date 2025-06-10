#include <iostream>
#include <locale.h>

#include<map>
#include<set>

#include<string>

#include"CBST.h"

using std::map;
using std::make_pair;

using std::set;

// 트리
	// 이진 트리 : 자식이 2개가 넘어가지 않는 구조
	// level : 부모로 부터 자식 까지의 깊이, 보통은 부모가 0 level
	// 가장 높은 level : 트리의 높이
	// Root Node : 0 level은 부모 노드가 없다. 부모가 존재하지 않는 노드
	// leaf Node : 트리의 높이가 가장 높은 노드는 자식 노드가 없다. 단말 노드라고도 부름, 자식이 없는 노드라고 생각
	
	// 완전 이진 트리 : root node부터 leaf node 까지 자식 노드를 2개씩으로 꽉 꽉 채워 나가는 트리
		// 배열로 구현
		// 자식 노드의 index는 부모의 index 번호의 2k + 1, 2k + 2 이다. k 는 부모노드의 index 이다.
		// 자식이 부모 노드의 index를 알려면 index번호에 -1 한 후 나누기 2를 한 후 나온 몫이 부모의 index이다. (index - 1)/2 에서 몫

	// 이진 탐색 트리 : 이진 트리 이지만 탐색을 위해 만들어진 이진트리 (Binary Search Tree), 이진 탐색이 가능하다.
		// 1.데이터가 정렬이 되어 있어야 함 -> 중요 !!
		// 2.문제를 절반으로 줄여나가면서 탐색을 함 ( 중간 index 로 접근 )
		// 3.중위 순회를 사용
		//					50
		//				/		 \
		//			30		  60
		//			/\			/\
		//		20	50	40  80
		//		이런식으로 키값(부모의 값) 보다 작으면 왼쪽 크면 오른쪽으로 배치 
		// 
		//  만약 50 20 60 300 400 30 10 순으로 값이 들어오면
		//					50한일 대학생 연수
		//				 / 	\
		//			 20		 60
		//			 /\			 \
		//		 10	 30		 300
		//									\
		//									400
		// 배열에는 {10, 20, 30, 50, 60, 300, 400} 이런식으로 저장이 됨
		// 
	// 순회
		// 전위 순회
			// 부모 > 왼쪽 > 오른쪽 으로 우선순위가 높음
			// {50, 20, 60, 10, 30, 300, 400}
		// 중위 순회
			// 왼쪽 > 부모 > 오른쪽
			// {10, 20, 30, 50, 60, 300, 400}
		// 후위 순회
			// 왼쪽 > 오른쪽 > 부모
			// {10, 30, 20, 400, 300, 60, 50}
	// 프로그래밍에서는 이진탐색트리만 가지고 구현하지 않는다 ( 입력 자체가 무작위로 들어올 경우 문제가 생길 수도 있음 )
	// self balanced(자가구현 기능)을 추가해야한다
	// AVL, Red-Black 등이 있음
// 그래프

#define MAN 1
#define WOMAN 2

struct tStdInfo
{
	wchar_t szName[20];
	unsigned char age;
	unsigned char gender;

	tStdInfo()
		: szName{}
		, age(0)
		, gender(0)
	{ }
	tStdInfo(const wchar_t* _pName, unsigned char _age, unsigned char _gender)
		: szName{}
		, age(_age)
		, gender(_gender)
	{
		// 첫번째 인자(목적지 시작 주소), 두번째 인자(들어갈 문자)
		wcscpy_s(szName, _pName);
	}
};

class MyClass
{
private:
	int a;

public:
	bool operator < (const MyClass& _other) const					// 이 객체를(this) 지금은 이걸 실행시키는 MyClass라는 객체를 바꾸지 않겠다. 객체의 멤버도 변경 불가.
	{
		if (a < _other.a)
		{
			return true;
		}
	}

	bool operator > (const MyClass& _other) const
	{
		if (a > _other.a)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

// enum	: 열거형
// 컴파일러가 아래와 같이 연속된 숫자로 받아들인다.
// 다른 enum이어도 enum내 멤버의 이름이 같은걸 사용하지 못한다.
// enum 클래스를 사용하면 어디에 있는 enum을 사용하겠다 라는걸 나타내줘야한다. ex) MY_TYPE::TYPE_6;
// 그리고 enum 자료형으로 보기 때문에 만약 다른 DataType으로 나타내고 싶으면 강제 캐스팅을 해줘야 한다. ex) int a = (int)MY_TYPE::TYPE_1;
// #define과 비슷하나 #define은 전처리, enum은 Symbol table에 남아있어 서식정보가 남아있는다. 그래서 디버깅 할때 #define은 그냥 옆에 숫자 정보만 넘어오지만 enum은 그게 무슨타입인지도 알려준다.
enum class MY_TYPE
{
	TYPE_1,		// 0
	TYPE_2,		// 1
	TYPE_3,		// 2
	TYPE_5 = 100,
	TYPE_6		// 101 이 들어옴
};

enum class OTHER_TYPE
{
	TYPE_1,

};

int main()
{

	// 이진 탐색(이진 탐색 트리와 다름)
	// 1. 정렬되어 있는 데이터에 적용 가능

	// 이진 탐색 트리
	// 1. 이진탐색을 사용 할 수 있게 고안된 이진트리
	// 2. 데이터 입력시 0(logN) 효율
	// 3. 대표적으로 map
	// 4. 탐색 효율은 0(logN)
	// 5. 트리의 모양이 밸런스가 유지되지 않으면 제대로 된 탐색 효율이 나오지 않는다.
		// 자가균형 필요 - AVL, Red/Black 등
	//

	// set
	// set은 red black 트리가 가능하다.
	// 이진 탐색트리 기반 자료 알고리즘을사용
	// set은 map보다 많이 사용하지 않음
	set<int> setInt;

	setInt.insert(100);

	// map
	// map은 typename을 2개 지정해줌
		// 첫번째 typename 을 key값( 비교의 데이터로 사용 ), 두번째 typename은 거기 안에 있는 추가적인 data 값
		//					
		//					100
		//					/ \
		//				 50	100
		// 이러한 값이 있을 때 100은 키값이고 그 안에 연결된 데이터들이 따로있다.
	map<std::wstring, tStdInfo> mapData;

	tStdInfo info(L"한강현", 30, MAN);
	tStdInfo info2(L"홍길동", 26, MAN);

	// make_pair
	// - 인자들을 묶음으로 만들어 pair객체를 만들어주는 함수
	mapData.insert(make_pair(L"한강현", info));
	mapData.insert(make_pair(L"홍길동", info2));

	map<std::wstring, tStdInfo>::iterator mapiter;
	mapiter = mapData.find(L"한강현");
	// 여기서 mapiter의 역할은 pair를 접근하는 역할이다.
	// 또한 iterator는 주소값을 받아오는 역할이기도 하다.

	// 여기에서 Vector나 LinkedList는 data type을 하나만 쓰는거지만, map은 여러개 Data type을 쓴다.

	//(*mapiter);						// 이거는 pair라는 구조체 형태를 접근한다는 의미이다.

	// pair는 구조체 템플릿으로써 pair<const wchar_t*, tStdInfo> 인 pair이다
	
	/*
	struct pair
	{
		const wchar_t* first;
		tStdInfo second;
	}
	*/
	// pair는 이러한 구조체 구조일것이다. 여기서 각각의 멤버를 따로 접근을 해야 값을 불러올 수 있다.
	// 이런식으로 하지만 이건 값이 이상하게 나옴 아마 wchar_t로 해서 그런듯, 주소값을 비교하게 되서

	_wsetlocale(LC_ALL, L"korean");

	std::wcout << (*mapiter).first << std::endl;
	std::wcout << (*mapiter).second.age << std::endl;
	std::wcout << (*mapiter).second.gender << std::endl;
	std::wcout << (*mapiter).second.szName << std::endl;

	std::cout << std::endl;

	std::wcout << mapiter->first << std::endl;
	std::wcout << mapiter->second.age << std::endl;
	std::wcout << mapiter->second.gender << std::endl;
	std::wcout << mapiter->second.szName << std::endl;

	std::cout << std::endl;

	mapiter = mapData.find(L"엄길동");		// 이러식으로 키값이 없을 경우 오류표현이 아니고 이러한경우 iterator는 end()상태가된다.(잘못찾았다고 iterator를 사용못하게는 안한다.)

	if (mapiter == mapData.end())
	{
		std::wcout << L"데이터를 찾을 수 없다." << std::endl;
	}
	// 참고로 cout은 char전용, wcout은 wchar_t 전용이긴 한데 한글인 경우 유니코드 같은걸 잘 설정해야한다. _wsetlocale(LC_ALL, L"korean"); 을 사용해도 된다.

	std::wstring str;				
	str = L"abcdef";
	// 이건 L"abcdef"의 주소를 받는게 아니라 객체에 대입을 하는 것이다.
	// = operator로 구현을 해서 대입을 받는다.
	// wstring 객체 안에 있는 문자열에 L"abcdef"를 받아온다.
	// wstring 문자 데이터를 따로 관리를 한다.
	// += operator를 통해 문자열 붙이기가 가능하다.
		// +는 새로운 문자열을 반환, +=는 자기 자신에 추가
	// 저거는 문자열 전용이라 문자 하나는 받아올 수 없다.
	// 원래 wchar는 문자열의 주소를 받아오는거다.
	// 그리고 처음부터 별도의 공간을 크게 할당하는게 아니라 동적할당으로 관리한다.
	// str[1] 같은것도 사용가능
	// 다양한 operator가 있다.

	// 여기서 일단 key로 wstring을 넣으면 wstring에서 <, > operator를 이용해 문자열끼리 비교해서 트리 구조에서 왼쪽으로갈지 오른쪽으로갈지 정한다.

	CBST<int, int> bstint;

	bstint.insert(make_bstpair(100, 0));
	
	bstint.insert(make_bstpair(150, 0));

	bstint.insert(make_bstpair(50, 0));

	CBST<int, int>::iterator mybstiter = bstint.begin();

	//mybstiter = bstint.find(150);
	//mybstiter = bstint.find(130);

	for (mybstiter = bstint.begin(); mybstiter != bstint.end(); ++mybstiter)
	{
		std::wcout << mybstiter->key << " " << mybstiter->data << std::endl;
	}

	return 0;
}