#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class Vector
{
public:
	Vector()
	{

	}
	~Vector()
	{
		if (_data)
			delete[] _data;

	}
	void push_back(T& value)
	{
		if (_size == _capacity)//현재 사이즈가 가득 찼을 경우
		{
			//메모리 확보
			int newCapacity = static_cast<int>(_capacity * 1.5f);
			if (newCapacity == _capacity)
			{
				newCapacity++;
			}
			reserve(newCapacity);
		}
		//데이터 저장
		_data[_size] = value;
		_size++;

	}
	void reserve(int capacity)
	{
		if (_capacity >= capacity)
			return;

		_capacity = capacity;
		T* newData = new T[_capacity];

		for (int i =0;i< _size;i++)
		{
			newData[i] = _data[i];
		}

		if (_data)
			delete[] _data;

		_data = newData;
	}

	T& operator[](const int pos) { return _data[pos]; }
	int size() { return _size; }
	int capacity() { return _capacity; }

	void clear()
	{
		if (_data)
		{
			delete[] _data;
			_data = new T[_capacity];
		}
		_size = 0;
	}
private:
	
	T* _data = nullptr;
	int _size = 0;
	int _capacity = 0;

};


int main()
{
	vector<int> v;
	
	//reserve는 capacity를 조절하는 것이고
	//resize는 데이터의 개수를 조절하는 것이다 capacity가 부족하지 않으면  건들지 않음 resize 양이 기존의 데이터보다 작을 경우 기존의 데이터를 전부 날림
	//v.resize(10, 0);
	
	for (int i = 0; i < 100; i++)
	{
		v.push_back(i);
		cout <<v[i] <<" "<< v.size() << " " << v.capacity() << endl;
	}
	v.resize(10, 0);
	v.clear();//클리어해도 크기가 줄지 않는다
	cout <<v.size() << " " << v.capacity() << endl;//size는 가지고 있는 데이터 //capacity는 벡터의 크기 용량
}
