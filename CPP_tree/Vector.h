#pragma once
#include<assert.h>

// Vector 구현
template<typename T>
class Vector
{
	// 필요 멤버 : data를 저장할 멤버(가변배열을 사용할거라 포인터 사용), 사이즈, 용량
	// 외부에서 접근을 쉽게 못하게 할 것 이므로 private으로 설정
private:
	T* v_data;
	int v_size;
	int v_capacity;

public:
	void push_back(const T& data);
	void resize(const int& resize);

public:
	T* data() { return v_data; }					// iterator나 다른곳에 벡터 데이터의 시작 주소를 주기 위해
	int size() { return v_size; }
	int capacity() { return v_capacity; }
	T& at(int& index) { return v_data[index]; }			// 다른곳에 특정 index의 값을 넘기기 위해
	T& operator[](int& index) { return v_data[index]; }

	// iterator용
public:
	class iterator;
	iterator begin();										// iterator에 벡터의 시작 정보를 넘겨줌. iterator를 사용하기 위해서(원래 지정이 안되있는걸 가정), &를 반환타입으로 사용하지 않는 이유는 참조할게 없어서
	iterator end();											// iterator에 벡터의 끝 정보를 넘겨줌.
	iterator erase(iterator& _iter);
	void clear() { v_size = 0; }

	// 생성자
public:
	Vector()
		: v_data(nullptr)
		, v_size(0)
		, v_capacity(8)					// 기본용량 설장
	{
		v_data = new T[8];			// 용량만큼 가변배열 설정
	}
	~Vector()
	{
		delete[] v_data;
	}

	// iterator
	class iterator
	{
		// 멤버 선언 : 벡터의 주소, data의 주소(오류체크용), index, iterator가 유효한지 파악하기 위해
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

		// 생성자
	public:
		iterator()
			: i_vec(nullptr)
			, i_data(nullptr)
			, i_index(-1)							// iterator가 end iterator (끝 index의 다음)을 나타냄
			, i_bValid(false)
		{ }
		iterator(Vector<T>* vec, T* data, int index)
			: i_vec(vec)
			, i_data(data)
			, i_index(index)
			, i_bValid(false)
		{
			// vector를 가리키고 있으면 이 iterator는 사용 가능하게 바꿔준다.
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
	// 오류체크
	// iterator가 가리키고있는 vector의 data와 iterator가 저장하고 있는 data의 정보가 일치한지 확인
	// end iterator인지 확인
	// iterator가 정상인지 확인
	if (i_vec->v_data != i_data || -1 == i_index || !i_bValid)
	{
		assert(nullptr);
	}

	// *를 사용할시 vector에 해당 index부분의 값을 반환함
	return i_vec->v_data[i_index];
}

template<typename T>
inline typename Vector<T>::iterator& Vector<T>::iterator::operator++()
{
	// 오류체크
	// iterator가 가리키고있는 vector의 data와 iterator가 저장하고 있는 data의 정보가 일치한지 확인
	// end iterator인지 확인
	// iterator가 정상인지 확인
	if (i_vec->v_data != i_data || -1 == i_index || !i_bValid)
	{
		assert(nullptr);
	}
	// iterator가 가리키고있는 부분이 마지막 index인 경우 (i_index == v_size - 1)
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
	// 생성자를 만들어 줘도 되나 이건 기본으로 구현이 됨
	iterator temp(*this);
	++(*this);

	return temp;
}

template<typename T>
inline typename Vector<T>::iterator& Vector<T>::iterator::operator--()
{
	// 오류체크
	// iterator가 가리키고 있는 data의 주소와 vector의 data주소가 다른지 확인
	// begin() 인지 확인
	// iterator가 정상인지 확인
	if (i_vec->v_data != i_data || 0 == i_index || !i_bValid)
	{
		assert(nullptr);
	}
	// end()인 경우
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
	// iterator의 정보와 다른 iterator의 정보 ( iterator를 활용한 정보를 iterator로 비교) if문을 써도 되지만 이렇게 써도 된다.
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
	// 재할당 사이즈가 용량보다 크거나 같을 때 2배씩
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
	// 아무것도 안들어와 있으면 end iterator를 반환
	if (0 == v_size)
	{
		return iterator(this, v_data, -1);
	}

	// 아니면 0번 index를 반환
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
	// iterator가 이 Vector를 가리키고 있는지 확인
	// iterator가 end()인지 확인
	// 이 iterator가 가리키고있는 index가 Vector의 사이즈보다 작은지 확인
	if (_iter.i_vec != this || end() == _iter || _iter.i_index >= v_size)
	{
		assert(nullptr);
	}
	// 마지막 index 제거시
	if (_iter.i_index == v_size - 1)
	{
		--v_size;
		return end();
	}

	// 다음 데이터를 하나씩 앞으로 옮김
	for (int i = _iter.i_index; i < v_size - 1; ++i)
	{
		v_data[i] = v_data[i + 1];
	}
	_iter.i_bValid = false;
	--v_size;

	return iterator(this, v_data, _iter.i_index);
}
