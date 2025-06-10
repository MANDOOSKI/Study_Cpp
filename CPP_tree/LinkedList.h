#pragma once
#include<assert.h>

// LinkedList����, template���� ������ ���̹Ƿ� header���Ͽ� ����

template<typename T>
struct Node
{
	// �������̹Ƿ� ������, �����, �������� ���� ����
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
	// ù��°, ����, ������
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
	// ��� �����ڷ� ����
	Node<T>* newNode = new Node<T>(data, l_tail, nullptr);

	// �ƹ� �����͵� ���� ���
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
	// ��� ����
	Node<T>* newNode = new Node<T>(data, nullptr, l_head);

	// �ƹ� �����͵� ���� ���
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
