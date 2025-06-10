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
	// �θ� ���
	// �ڽ� ���
	Pair<Key, Data> pair;
	Node<Key, Data>* arrNode[(int)NODE_TYPE::END];

	bool IsRoot()
	{
		// ������ ��Ʈ���� Ȯ��
		if (nullptr == arrNode[(int)NODE_TYPE::PARENT])
			return true;
		return false;
	}

	bool IsLeftChild()
	{
		// �θ��� ���ʳ��� ���� ����� �ּҰ� ������ Ȯ��
		if (arrNode[(int)NODE_TYPE::PARENT]->arrNode[(int)NODE_TYPE::LCHILD] == this)
			return true;
		return false;
	}

	bool IsRightChild()
	{
		// �θ��� �����ʳ��� ���� ����� �ּҰ� ������ Ȯ��
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
	Node<Key, Data>* root;		// ��Ʈ��� �ּ�
	int size;			// ������ ����

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
		Node<Key, Data>* pNode;				// nullptr�� ����ų �� end()�� ģ��.

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
			// end iter�� ���
			// assert () ���� ()�� ���ǽ��̴� ���̸� �׳� �Ѿ�� �����̸� ����â�� ����ȴ�.
			assert(pNode);
			return pNode->pair;
		}

		const Pair<Key, Data>* operator ->()
		{
			// end iter�� ���
			// assert () ���� ()�� ���ǽ��̴� ���̸� �׳� �Ѿ�� �����̸� ����â�� ����ȴ�.
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

	// ������ �����Ͷ��
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
	// ������ ���� ����
	++size;

	return true;
}

template<typename Key, typename Data>
inline Node<Key, Data>* CBST<Key, Data>::GetInOrderSuccesor(Node<Key, Data>* _pNode)
{
	Node<Key, Data>* temp = nullptr;
	// 1. ������ �ڽ��� �ִ� ���, ������ �ڽ����� ����, ���� �ڽ��� ���� �� ���� �������� ������
	if (nullptr != _pNode->arrNode[(int)NODE_TYPE::RCHILD])
	{
		temp = _pNode->arrNode[(int)NODE_TYPE::RCHILD];

		while (temp->arrNode[(int)NODE_TYPE::LCHILD])
		{
			temp = temp->arrNode[(int)NODE_TYPE::LCHILD];
		}
	}
	// 2. �θ�� ���� ���� �ڽ��� �� ���� ���� �ö�
	//    - �׶� �θ� �ļ���
	else
	{
		temp = _pNode;
		while (true)
		{
			// ���̻� �������� �ö� �� ����. ==> ������ ��忴��.
			if (temp->IsRoot())
				return nullptr;

			// �θ�� ���� �����ڽ����� üũ
			if (temp->IsLeftChild())
			{
				// �׶� �θ� �ļ���
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
	// 1. ���� �ڽ��� �ִ� ���, ���� �ڽ����� ����, ������ �ڽ��� ���� �� ���� �������� ������
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
	// ���� ��ȸ������ ���� ���� ������ ���۵ȴ�.
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
	// _find�� ���� ���� ã�� ���̴�.
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
			// ��ã�� ��� temp = nullptr => end iterator
			temp = nullptr;
			break;
		}
	}
	return iterator(this, temp);
}
