#include <iostream>
#include <vector>
#include <stack>
using namespace std;
//stack first in last out


template <typename T>
class Stack
{
public:
	void push(const T& value)
	{
		_container.push_back(value);
	}
	void pop()
	{
		_container.pop_back();
	}

	T& top()
	{
		return _container.back();
	}
	bool empty()
	{
		return _container.empty();
	}
	int size()
	{
		return _container.size();
	}
private:
	vector<T> _container;
};

int main()
{
	Stack<int> s;

	s.push(1);
	s.push(2);
	s.push(3);
	s.push(4);
	s.push(5);


	while (s.empty() == false)
	{
		int data = s.top();
		s.pop();
		cout << data<<endl;
	}

	int size = s.size();
}