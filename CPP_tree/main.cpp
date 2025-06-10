#include <iostream>
#include <locale.h>

#include<map>
#include<set>

#include<string>

#include"CBST.h"

using std::map;
using std::make_pair;

using std::set;

// Ʈ��
	// ���� Ʈ�� : �ڽ��� 2���� �Ѿ�� �ʴ� ����
	// level : �θ�� ���� �ڽ� ������ ����, ������ �θ� 0 level
	// ���� ���� level : Ʈ���� ����
	// Root Node : 0 level�� �θ� ��尡 ����. �θ� �������� �ʴ� ���
	// leaf Node : Ʈ���� ���̰� ���� ���� ���� �ڽ� ��尡 ����. �ܸ� ����� �θ�, �ڽ��� ���� ����� ����
	
	// ���� ���� Ʈ�� : root node���� leaf node ���� �ڽ� ��带 2�������� �� �� ä�� ������ Ʈ��
		// �迭�� ����
		// �ڽ� ����� index�� �θ��� index ��ȣ�� 2k + 1, 2k + 2 �̴�. k �� �θ����� index �̴�.
		// �ڽ��� �θ� ����� index�� �˷��� index��ȣ�� -1 �� �� ������ 2�� �� �� ���� ���� �θ��� index�̴�. (index - 1)/2 ���� ��

	// ���� Ž�� Ʈ�� : ���� Ʈ�� ������ Ž���� ���� ������� ����Ʈ�� (Binary Search Tree), ���� Ž���� �����ϴ�.
		// 1.�����Ͱ� ������ �Ǿ� �־�� �� -> �߿� !!
		// 2.������ �������� �ٿ������鼭 Ž���� �� ( �߰� index �� ���� )
		// 3.���� ��ȸ�� ���
		//					50
		//				/		 \
		//			30		  60
		//			/\			/\
		//		20	50	40  80
		//		�̷������� Ű��(�θ��� ��) ���� ������ ���� ũ�� ���������� ��ġ 
		// 
		//  ���� 50 20 60 300 400 30 10 ������ ���� ������
		//					50���� ���л� ����
		//				 / 	\
		//			 20		 60
		//			 /\			 \
		//		 10	 30		 300
		//									\
		//									400
		// �迭���� {10, 20, 30, 50, 60, 300, 400} �̷������� ������ ��
		// 
	// ��ȸ
		// ���� ��ȸ
			// �θ� > ���� > ������ ���� �켱������ ����
			// {50, 20, 60, 10, 30, 300, 400}
		// ���� ��ȸ
			// ���� > �θ� > ������
			// {10, 20, 30, 50, 60, 300, 400}
		// ���� ��ȸ
			// ���� > ������ > �θ�
			// {10, 30, 20, 400, 300, 60, 50}
	// ���α׷��ֿ����� ����Ž��Ʈ���� ������ �������� �ʴ´� ( �Է� ��ü�� �������� ���� ��� ������ ���� ���� ���� )
	// self balanced(�ڰ����� ���)�� �߰��ؾ��Ѵ�
	// AVL, Red-Black ���� ����
// �׷���

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
		// ù��° ����(������ ���� �ּ�), �ι�° ����(�� ����)
		wcscpy_s(szName, _pName);
	}
};

class MyClass
{
private:
	int a;

public:
	bool operator < (const MyClass& _other) const					// �� ��ü��(this) ������ �̰� �����Ű�� MyClass��� ��ü�� �ٲ��� �ʰڴ�. ��ü�� ����� ���� �Ұ�.
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

// enum	: ������
// �����Ϸ��� �Ʒ��� ���� ���ӵ� ���ڷ� �޾Ƶ��δ�.
// �ٸ� enum�̾ enum�� ����� �̸��� ������ ������� ���Ѵ�.
// enum Ŭ������ ����ϸ� ��� �ִ� enum�� ����ϰڴ� ��°� ��Ÿ������Ѵ�. ex) MY_TYPE::TYPE_6;
// �׸��� enum �ڷ������� ���� ������ ���� �ٸ� DataType���� ��Ÿ���� ������ ���� ĳ������ ����� �Ѵ�. ex) int a = (int)MY_TYPE::TYPE_1;
// #define�� ����ϳ� #define�� ��ó��, enum�� Symbol table�� �����־� ���������� �����ִ´�. �׷��� ����� �Ҷ� #define�� �׳� ���� ���� ������ �Ѿ������ enum�� �װ� ����Ÿ�������� �˷��ش�.
enum class MY_TYPE
{
	TYPE_1,		// 0
	TYPE_2,		// 1
	TYPE_3,		// 2
	TYPE_5 = 100,
	TYPE_6		// 101 �� ����
};

enum class OTHER_TYPE
{
	TYPE_1,

};

int main()
{

	// ���� Ž��(���� Ž�� Ʈ���� �ٸ�)
	// 1. ���ĵǾ� �ִ� �����Ϳ� ���� ����

	// ���� Ž�� Ʈ��
	// 1. ����Ž���� ��� �� �� �ְ� ��ȵ� ����Ʈ��
	// 2. ������ �Է½� 0(logN) ȿ��
	// 3. ��ǥ������ map
	// 4. Ž�� ȿ���� 0(logN)
	// 5. Ʈ���� ����� �뷱���� �������� ������ ����� �� Ž�� ȿ���� ������ �ʴ´�.
		// �ڰ����� �ʿ� - AVL, Red/Black ��
	//

	// set
	// set�� red black Ʈ���� �����ϴ�.
	// ���� Ž��Ʈ�� ��� �ڷ� �˰��������
	// set�� map���� ���� ������� ����
	set<int> setInt;

	setInt.insert(100);

	// map
	// map�� typename�� 2�� ��������
		// ù��° typename �� key��( ���� �����ͷ� ��� ), �ι�° typename�� �ű� �ȿ� �ִ� �߰����� data ��
		//					
		//					100
		//					/ \
		//				 50	100
		// �̷��� ���� ���� �� 100�� Ű���̰� �� �ȿ� ����� �����͵��� �����ִ�.
	map<std::wstring, tStdInfo> mapData;

	tStdInfo info(L"�Ѱ���", 30, MAN);
	tStdInfo info2(L"ȫ�浿", 26, MAN);

	// make_pair
	// - ���ڵ��� �������� ����� pair��ü�� ������ִ� �Լ�
	mapData.insert(make_pair(L"�Ѱ���", info));
	mapData.insert(make_pair(L"ȫ�浿", info2));

	map<std::wstring, tStdInfo>::iterator mapiter;
	mapiter = mapData.find(L"�Ѱ���");
	// ���⼭ mapiter�� ������ pair�� �����ϴ� �����̴�.
	// ���� iterator�� �ּҰ��� �޾ƿ��� �����̱⵵ �ϴ�.

	// ���⿡�� Vector�� LinkedList�� data type�� �ϳ��� ���°�����, map�� ������ Data type�� ����.

	//(*mapiter);						// �̰Ŵ� pair��� ����ü ���¸� �����Ѵٴ� �ǹ��̴�.

	// pair�� ����ü ���ø����ν� pair<const wchar_t*, tStdInfo> �� pair�̴�
	
	/*
	struct pair
	{
		const wchar_t* first;
		tStdInfo second;
	}
	*/
	// pair�� �̷��� ����ü �����ϰ��̴�. ���⼭ ������ ����� ���� ������ �ؾ� ���� �ҷ��� �� �ִ�.
	// �̷������� ������ �̰� ���� �̻��ϰ� ���� �Ƹ� wchar_t�� �ؼ� �׷���, �ּҰ��� ���ϰ� �Ǽ�

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

	mapiter = mapData.find(L"���浿");		// �̷������� Ű���� ���� ��� ����ǥ���� �ƴϰ� �̷��Ѱ�� iterator�� end()���°��ȴ�.(�߸�ã�Ҵٰ� iterator�� �����ϰԴ� ���Ѵ�.)

	if (mapiter == mapData.end())
	{
		std::wcout << L"�����͸� ã�� �� ����." << std::endl;
	}
	// ����� cout�� char����, wcout�� wchar_t �����̱� �ѵ� �ѱ��� ��� �����ڵ� ������ �� �����ؾ��Ѵ�. _wsetlocale(LC_ALL, L"korean"); �� ����ص� �ȴ�.

	std::wstring str;				
	str = L"abcdef";
	// �̰� L"abcdef"�� �ּҸ� �޴°� �ƴ϶� ��ü�� ������ �ϴ� ���̴�.
	// = operator�� ������ �ؼ� ������ �޴´�.
	// wstring ��ü �ȿ� �ִ� ���ڿ��� L"abcdef"�� �޾ƿ´�.
	// wstring ���� �����͸� ���� ������ �Ѵ�.
	// += operator�� ���� ���ڿ� ���̱Ⱑ �����ϴ�.
		// +�� ���ο� ���ڿ��� ��ȯ, +=�� �ڱ� �ڽſ� �߰�
	// ���Ŵ� ���ڿ� �����̶� ���� �ϳ��� �޾ƿ� �� ����.
	// ���� wchar�� ���ڿ��� �ּҸ� �޾ƿ��°Ŵ�.
	// �׸��� ó������ ������ ������ ũ�� �Ҵ��ϴ°� �ƴ϶� �����Ҵ����� �����Ѵ�.
	// str[1] �����͵� ��밡��
	// �پ��� operator�� �ִ�.

	// ���⼭ �ϴ� key�� wstring�� ������ wstring���� <, > operator�� �̿��� ���ڿ����� ���ؼ� Ʈ�� �������� �������ΰ��� ���������ΰ��� ���Ѵ�.

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