#pragma once
#include <assert.h>

enum class NODE_TYPE
{
	PARENT,		// 0
	LCHILD,		// 1
	RCHILD,		// 2
	END,			// 3
};

template<typename Key, typename Data>
struct Pair
{
	Key key;
	Data data;

	Pair() {}
	Pair(const Key& _key, const Data& _data)
		: key(_key)
		, data(_data)
	{ }
};

template<typename Key, typename Data>
Pair<Key, Data> make_bstpair(const Key& _key, const Data& _data)
{
	return Pair<Key, Data>{ _key, _data };
}

template <typename Key, typename Data>
struct Node
{
	// data (pair)
	// 부모 노드
	// 자식 노드
	Pair<Key, Data> pair;
	Node<Key, Data>* arrNode[(int)NODE_TYPE::END];

	bool IsRoot()
	{
		// 본인이 루트인지 확인
		if (nullptr == arrNode[(int)NODE_TYPE::PARENT])
			return true;
		return false;
	}

	bool IsLeftChild()
	{
		// 부모의 왼쪽노드랑 지금 노드의 주소가 같은지 확인
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
			return true;
		return false;
	}

	bool IsRightChild()
	{
		// 부모의 오른쪽노드랑 지금 노드의 주소가 같은지 확인
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::RCHILD] == this)
			return true;
		return false;
	}

	Node()
		: pair()
		, arrNode{}
	{ }

	Node(const Pair<Key,Data>& _pair, Node<Key,Data>* _parent, Node<Key,Data>* _lChild, Node<Key,Data>* _rChild)
		: pair(_pair)
		, arrNode{_parent, _lChild, _rChild}
	{ }
};

template <typename Key, typename Data>
class CBST
{
private:
	Node<Key, Data>* root;		// 루트노드 주소
	int size;			// 데이터 개수

public:
	bool insert(const Pair<Key, Data>& _pair);
	Node<Key, Data>* GetInOrderSuccesor(Node<Key, Data>* _pNode);
	Node<Key, Data>* GetInOrderPredecessor(Node<Key, Data>* _pNode);

public:
	class iterator;
	iterator begin();
	iterator end();
	iterator find(const Key& _find);



public:
	CBST()
		: root(nullptr)
		, size(0)
	{ }

	class iterator
	{
	private:
		CBST<Key, Data>* pBst;
		Node<Key, Data>* pNode;				// nullptr을 가리킬 때 end()라 친다.

	public:
		bool operator == (const iterator& _other)
		{
			return pBst == _other.pBst && pNode == _other.pNode;
		}
		bool operator != (const iterator& _other)
		{
			return !(*this == _other);
		}

		const Pair<Key, Data>& operator *()
		{
			// end iter인 경우
			// assert () 에서 ()는 조건식이다 참이면 그냥 넘어가고 거짓이면 오류창이 실행된다.
			assert(pNode);
			return pNode->pair;
		}

		const Pair<Key, Data>* operator ->()
		{
			// end iter인 경우
			// assert () 에서 ()는 조건식이다 참이면 그냥 넘어가고 거짓이면 오류창이 실행된다.
			assert(pNode);
			return &pNode->pair;
		}
		iterator& operator ++()
		{
			pNode = pBst->GetInOrderSuccesor(pNode);
			return *this;
		}

	public:
		iterator()
			: pBst(nullptr)
			, pNode(nullptr)
		{ }

		iterator(CBST<Key, Data>* _pBst, Node<Key, Data>* _pNode)
			: pBst(_pBst)
			, pNode(_pNode)
		{ }
	};
};

template<typename Key, typename Data>
inline bool CBST<Key, Data>::insert(const Pair<Key, Data>& _pair)
{
	Node<Key, Data>* newNode = new Node<Key, Data>(_pair, nullptr, nullptr, nullptr);

	// 최초의 데이터라면
	if (nullptr == root)
	{
		root = newNode;
	}
	else
	{
		Node<Key, Data>* temp = root;
		NODE_TYPE node_type = NODE_TYPE::END;
		while (true)
		{
			if (temp->pair.key < newNode->pair.key)
				node_type = NODE_TYPE::RCHILD;
			else if (temp->pair.key > newNode->pair.key)
				node_type = NODE_TYPE::LCHILD;
			else
				return false;

			if (nullptr == temp->arrNode[(int)node_type])
			{
				temp->arrNode[(int)node_type] = newNode;
				newNode->arrNode[(int)NODE_TYPE::PARENT] = temp;
				break;
			}
			else
			{
				temp = temp->arrNode[(int)node_type];
			}
		}
		
	}
	// 데이터 개수 증가
	++size;

	return true;
}

template<typename Key, typename Data>
inline Node<Key, Data>* CBST<Key, Data>::GetInOrderSuccesor(Node<Key, Data>* _pNode)
{
	Node<Key, Data>* temp = nullptr;
	// 1. 오른쪽 자식이 있는 경우, 오른쪽 자식으로 가서, 왼쪽 자식이 없을 때 까지 왼쪽으로 내려감
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		temp = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (temp->arrNode[(int)NODE_TYPE::LCHILD])
		{
			temp = temp->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	// 2. 부모로 부터 왼쪽 자식일 때 까지 위로 올라감
	//    - 그때 부모가 후속자
	else
	{
		temp = _pNode;
		while (true)
		{
			// 더이상 위쪽으로 올라갈 수 없다. ==> 마지막 노드였다.
			if (temp->IsRoot())
				return nullptr;

			// 부모로 부터 왼쪽자식인지 체크
			if (temp->IsLeftChild())
			{
				// 그때 부모가 후속자
				temp = temp->arrNode[(int)NODE_TYPE::PARENT];
				break;
			}
			else
			{
				temp = temp->arrNode[(int)NODE_TYPE::PARENT];
			}
	
		}
	}

	return temp;
}

template<typename Key, typename Data>
inline Node<Key, Data>* CBST<Key, Data>::GetInOrderPredecessor(Node<Key, Data>* _pNode)
{
	Node<Key, Data>* temp = nullptr;
	// 1. 왼쪽 자식이 있는 경우, 왼쪽 자식으로 가서, 오른쪽 자식이 없을 때 까지 왼쪽으로 내려감
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::LCHILD])
	{
		temp = _pNode->arrNode[(int)NODE_TYPE::LCHILD];

		while (temp->arrNode[(int)NODE_TYPE::RCHILD])
		{
			temp = temp->arrNode[(int)NODE_TYPE::RCHILD];
		}
	}
	
	return temp;
}

template<typename Key, typename Data>
inline typename CBST<Key, Data>::iterator CBST<Key, Data>::begin()
{
	// 중위 순회에서는 가장 왼쪽 노드먼저 시작된다.
	Node<Key, Data>* temp = root;
	while (temp->arrNode[(int)NODE_TYPE::LCHILD])
	{
		temp = temp->arrNode[(int)NODE_TYPE::LCHILD];
	}
	return iterator(this, temp);
}

template<typename Key, typename Data>
inline typename CBST<Key, Data>::iterator CBST<Key, Data>::end()
{
	return iterator(this, nullptr);
}

template<typename Key, typename Data>
inline typename CBST<Key, Data>::iterator CBST<Key, Data>::find(const Key& _find)
{
	// _find와 같은 것을 찾을 것이다.
	Node<Key, Data>* temp = root;
	NODE_TYPE node_type = NODE_TYPE::END;
	while (true)
	{
		if (temp->pair.key > _find)
			node_type = NODE_TYPE::LCHILD;
		else if (temp->pair.key < _find)
			node_type = NODE_TYPE::RCHILD;
		else
			break;

		if (nullptr != temp->arrNode[(int)node_type])
		{
			temp = temp->arrNode[(int)node_type];
		}
		else
		{
			// 못찾은 경우 temp = nullptr => end iterator
			temp = nullptr;
			break;
		}
	}
	return iterator(this, temp);
}
