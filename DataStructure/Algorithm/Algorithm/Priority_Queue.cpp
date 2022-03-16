#include <iostream>
#include <vector>
#include <queue>

using namespace std;


template<typename T, typename Container = vector<T>, typename Predicate = less<T>>
class PriorityQueue
{
public:
	void push(const T& data)
	{
		//�켱 heap ������ �����ش�
		_heap.push_back(data);
		//����
		int now = static_cast<int>(_heap.size())-1;
		//��Ʈ ��� ���� ����
		while (now > 0)
		{
			int next = (now-1)/2;
			//predicate�� ���� ������ ��ü
			if (_predicate(_heap[now],_heap[next]))
				break;
			swap(_heap[now],_heap[next]);
			//�ٲٴ� �������� �ε����� ����
			now = next;
		}
	}
	void pop()
	{
		//������ ������ ��Ҹ� �ڷ� ������
		_heap[0] = _heap.back();
		//�ǵ��� ��� ����
		_heap.pop_back();
		
		int now =0;
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2*now + 2;
			//�ڽ��� �ִ��� Ȯ��
			if(left>= (int)_heap.size())
				break;
			int next = now;

			//���ʰ� ��
			if (_predicate(_heap[next], _heap[left]))
				next = left;
			//ū���� �����ʰ� ��
			if (right < (int)_heap.size()&& _predicate(_heap[next], _heap[right]))
				next = right; 
			//next�� now�� ������ break
			if(next==now)
				break;

			swap(_heap[now],_heap[next]);
			now = next;
		}
	}
	T& top()
	{
		return _heap[0];
	}

	bool empty()
	{
		return _heap.empty();
	}

private:

	Container _heap = {};
	Predicate _predicate = {};
};


int main()
{
	
	
	//template Ȱ���Ͽ��� ����
	PriorityQueue<int,vector<int>,greater<int>> pq;//�켱���� ť ���� ������ �������

	pq.push(400);
	pq.push(100);
	pq.push(200);
	pq.push(300);


	while (pq.empty() == false)
	{
		int value = pq.top();

		pq.pop();

		cout<<value<<endl;
	}




	////stl Ȱ���Ͽ��� ����
	//priority_queue<int,vector<int>,less<int>> pq;//�켱���� ť ���� ������ �������	 less ū�� ���� ��� ����Ѵ� greater ������ ���� ���
	//
	//pq.push(400);
	//pq.push(100);
	//pq.push(200);
	//pq.push(300);
	//
	//
	//while (pq.empty() == false)
	//{
	//	int value = pq.top();
	//
	//	pq.pop();
	//
	//	//cout<<value<<endl;
	//}
}