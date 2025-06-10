#pragma once
#include<assert.h>

// LinkedList구현, template으로 구현할 것이므로 header파일에 구현

template<typename T>
struct Node
{
	// 연결형이므로 데이터, 전노드, 다음노드로 변수 설정
	T n_data;
	Node<T>* n_prev;
	Node<T>* n_next;

	Node(T data, Node<T>* prev, Node<T> next)
		: n_data(data)
		, n_prev(prev)
		, n_next(next)
};

template<typename T>
class LinkedList
{
	// 첫번째, 꼬리, 사이즈
private:
	Node<T>* l_head;
	Node<T>* l_tail;
	int l_size;

public:
	void push_back(const T& data);
	void push_front(const T& data);

public:
	LinkedList()
		: l_head(nullptr)
		, l_tail(nullptr)
		, l_size(0)
	{ }
};

template<typename T>
inline void LinkedList<T>::push_back(const T& data)
{
	// 노드 생성자로 생성
	Node<T>* newNode = new Node<T>(data, l_tail, nullptr);

	// 아무 데이터도 없는 경우
	if (nullptr == l_head || 0 == l_size)
	{
		l_head = newNode;
		l_tail = newNode;
	}
	else
	{
		l_tail->n_next = newNode;
		l_tail = newNode;
	}
	++l_size;
}

template<typename T>
inline void LinkedList<T>::push_front(const T& data)
{
	// 노드 생성
	Node<T>* newNode = new Node<T>(data, nullptr, l_head);

	// 아무 데이터도 없는 경우
	if (nullptr == l_head || 0 == l_size)
	{
		l_head = newNode;
		l_tail = newNode;
	}
	else
	{
		l_head->n_prev = newNode;
		l_head = newNode;
	}
	++l_size;
}
