#include <iostream>
#include <queue>
#include <list>
using namespace std;
template<typename T>

class ArrayQueue
{
public:
	ArrayQueue()
	{
		_container.resize(100);
	}


	void push(const T& value)
	{
		if (_size == _container.size())
		{
			//공간 증설
			int newSize = max(1,_size * 2);
			vector<T> newData;
			newData.resize(newSize);
			//데이터 복사
			for (int i = 0; i < _size; i++)
			{
				int index = ((int)_front + i) % _container.size();
				newData[i] = _container[index];
			}
			//세팅
			_container.swap(newData);
			_front = 0;
			_back = _size;
		}
		//데이터 추가
		_container[_back] = value;
		_back= ((int)_back+1)%_container.size();
		_size++;
	}
	void pop()
	{
		_front = ((int)_front + 1) % _container.size();
		_size--;
	}
	T& front()
	{
		return _container[_front];
	}
	bool empty()
	{
		return _size==0;
	}
	int size() { return _container.size(); }
private:
	vector<T> _container;
	int _front=0;
	int _back=0;
	int _size=0;
};

template<typename T>
class ListQueue
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}
	void pop()
	{
		_container.pop_front();
		//_container.erase(_container.begin());
	}
	T& front()
	{
		return _container.front();
	}
	bool empty()
	{
		return _container.empty();
	}
	int size() { return _container.size(); }
private:
	list<T> _container;
};


int main()
{
	ArrayQueue<int> q;

	for (int i = 0; i < 300; i++)
	{
		q.push(i);
	}

	while (!q.empty())
	{
		int value = q.front();
		q.pop();
		cout << value << endl;
	}

	int size = q.size();
}