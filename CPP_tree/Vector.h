#pragma once
#include<assert.h>

// Vector ����
template<typename T>
class Vector
{
	// �ʿ� ��� : data�� ������ ���(�����迭�� ����ҰŶ� ������ ���), ������, �뷮
	// �ܺο��� ������ ���� ���ϰ� �� �� �̹Ƿ� private���� ����
private:
	T* v_data;
	int v_size;
	int v_capacity;

public:
	void push_back(const T& data);
	void resize(const int& resize);

public:
	T* data() { return v_data; }					// iterator�� �ٸ����� ���� �������� ���� �ּҸ� �ֱ� ����
	int size() { return v_size; }
	int capacity() { return v_capacity; }
	T& at(int& index) { return v_data[index]; }			// �ٸ����� Ư�� index�� ���� �ѱ�� ����
	T& operator[](int& index) { return v_data[index]; }

	// iterator��
public:
	class iterator;
	iterator begin();										// iterator�� ������ ���� ������ �Ѱ���. iterator�� ����ϱ� ���ؼ�(���� ������ �ȵ��ִ°� ����), &�� ��ȯŸ������ ������� �ʴ� ������ �����Ұ� ���
	iterator end();											// iterator�� ������ �� ������ �Ѱ���.
	iterator erase(iterator& _iter);
	void clear() { v_size = 0; }

	// ������
public:
	Vector()
		: v_data(nullptr)
		, v_size(0)
		, v_capacity(8)					// �⺻�뷮 ����
	{
		v_data = new T[8];			// �뷮��ŭ �����迭 ����
	}
	~Vector()
	{
		delete[] v_data;
	}

	// iterator
	class iterator
	{
		// ��� ���� : ������ �ּ�, data�� �ּ�(����üũ��), index, iterator�� ��ȿ���� �ľ��ϱ� ����
	private:
		Vector<T>* i_vec;
		T* i_data;
		int i_index;
		bool i_bValid;

		//operator
	public:
		T& operator* ();
		iterator& operator ++ ();
		iterator operator ++ (int);
		iterator& operator -- ();
		iterator operator -- (int);
		bool operator == (const iterator& _other);
		bool operator != (const iterator& _other);

		// ������
	public:
		iterator()
			: i_vec(nullptr)
			, i_data(nullptr)
			, i_index(-1)							// iterator�� end iterator (�� index�� ����)�� ��Ÿ��
			, i_bValid(false)
		{ }
		iterator(Vector<T>* vec, T* data, int index)
			: i_vec(vec)
			, i_data(data)
			, i_index(index)
			, i_bValid(false)
		{
			// vector�� ����Ű�� ������ �� iterator�� ��� �����ϰ� �ٲ��ش�.
			if (nullptr != i_vec && -1 == i_index)
			{
				i_bValid = true;
			}
		}

		~iterator(){}
	};
};

template<typename T>
inline T& Vector<T>::iterator::operator* ()
{
	// ����üũ
	// iterator�� ����Ű���ִ� vector�� data�� iterator�� �����ϰ� �ִ� data�� ������ ��ġ���� Ȯ��
	// end iterator���� Ȯ��
	// iterator�� �������� Ȯ��
	if (i_vec->v_data != i_data || -1 == i_index || !i_bValid)
	{
		assert(nullptr);
	}

	// *�� ����ҽ� vector�� �ش� index�κ��� ���� ��ȯ��
	return i_vec->v_data[i_index];
}

template<typename T>
inline typename Vector<T>::iterator& Vector<T>::iterator::operator++()
{
	// ����üũ
	// iterator�� ����Ű���ִ� vector�� data�� iterator�� �����ϰ� �ִ� data�� ������ ��ġ���� Ȯ��
	// end iterator���� Ȯ��
	// iterator�� �������� Ȯ��
	if (i_vec->v_data != i_data || -1 == i_index || !i_bValid)
	{
		assert(nullptr);
	}
	// iterator�� ����Ű���ִ� �κ��� ������ index�� ��� (i_index == v_size - 1)
	else if (i_index == v_size - 1)
	{
		i_index = -1;
	}
	else
	{
		++i_index;
	}

	return *this;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::iterator::operator++(int)
{
	// �����ڸ� ����� �൵ �ǳ� �̰� �⺻���� ������ ��
	iterator temp(*this);
	++(*this);

	return temp;
}

template<typename T>
inline typename Vector<T>::iterator& Vector<T>::iterator::operator--()
{
	// ����üũ
	// iterator�� ����Ű�� �ִ� data�� �ּҿ� vector�� data�ּҰ� �ٸ��� Ȯ��
	// begin() ���� Ȯ��
	// iterator�� �������� Ȯ��
	if (i_vec->v_data != i_data || 0 == i_index || !i_bValid)
	{
		assert(nullptr);
	}
	// end()�� ���
	else if (-1 == i_index)
	{
		i_index = v_size - 1;
	}
	else
	{
		--i_index;
	}

	return *this;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::iterator::operator--(int)
{
	iterator temp(*this);
	--(*this);

	return temp;
}

template<typename T>
inline bool Vector<T>::iterator::operator==(const iterator& _other)
{
	// iterator�� ������ �ٸ� iterator�� ���� ( iterator�� Ȱ���� ������ iterator�� ��) if���� �ᵵ ������ �̷��� �ᵵ �ȴ�.
	return i_vec == _other.i_vec && i_data == _other.i_data && i_index == _other.i_index;
}

template<typename T>
inline bool Vector<T>::iterator::operator!=(const iterator& _other)
{
	return !(*this == _other);
}

template<typename T>
inline void Vector<T>::push_back(const T& data)
{
	// ���Ҵ� ����� �뷮���� ũ�ų� ���� �� 2�辿
	if (v_size >= v_capacity)
	{
		resize(v_capacity * 2);
	}
	v_data[v_size++] = data;
}

template<typename T>
inline void Vector<T>::resize(const int& resize)
{
	if (resize <= v_capacity || resize < 0)
	{
		assert(nullptr);
	}
	T* newData = new T[resize];
	for (int i = 0; i < v_size; ++i)
	{
		newData[i] = v_data[i];
	}
	delete[] v_data;
	v_data = newData;
	v_capacity = resize;
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::begin()
{
	// �ƹ��͵� �ȵ��� ������ end iterator�� ��ȯ
	if (0 == v_size)
	{
		return iterator(this, v_data, -1);
	}

	// �ƴϸ� 0�� index�� ��ȯ
	return iterator(this, v_data, 0);
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::end()
{
	return iterator(this, v_data, -1);
}

template<typename T>
inline typename Vector<T>::iterator Vector<T>::erase(iterator& _iter)
{
	// iterator�� �� Vector�� ����Ű�� �ִ��� Ȯ��
	// iterator�� end()���� Ȯ��
	// �� iterator�� ����Ű���ִ� index�� Vector�� ������� ������ Ȯ��
	if (_iter.i_vec != this || end() == _iter || _iter.i_index >= v_size)
	{
		assert(nullptr);
	}
	// ������ index ���Ž�
	if (_iter.i_index == v_size - 1)
	{
		--v_size;
		return end();
	}

	// ���� �����͸� �ϳ��� ������ �ű�
	for (int i = _iter.i_index; i < v_size - 1; ++i)
	{
		v_data[i] = v_data[i + 1];
	}
	_iter.i_bValid = false;
	--v_size;

	return iterator(this, v_data, _iter.i_index);
}
