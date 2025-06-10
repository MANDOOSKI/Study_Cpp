#pragma once

template<typename K, typename D>
class MapTree
{
private:
	struct Node
	{
		K key;
		D data;
		Node<T>* left;
		Node<T>* right;
	};

private:
	Node* root;

	Node* insert(Node* _node, const K& _key, const D& _data);

public:
	void insert(const K& _key, const D& _data)
	{
		root = insert(root, _key, _data);
	}

public:
	MapTree()
		: root(nullptr){ }
	


};

template<typename K, typename D>
inline typename MapTree<K, D>::Node* MapTree<K, D>::insert(Node* _node, const K& _key, const D& _data)
{
	if (!_node)
	{
		return new Node<K, D>;
	}
	if (k < _node->key)
	{
		_node->left = insert(_node->left, _key, _data);
	}
	else if (k > _node->key)
	{
		_node->right = insert(_node->right, _key, _data);
	}
	else
	{
		_node->data = _data;
	}
	return node;
}
