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
		//우선 heap 구조를 맞춰준다
		_heap.push_back(data);
		//정렬
		int now = static_cast<int>(_heap.size())-1;
		//루트 노드 까지 정렬
		while (now > 0)
		{
			int next = (now-1)/2;
			//predicate에 따라서 데이터 교체
			if (_predicate(_heap[now],_heap[next]))
				break;
			swap(_heap[now],_heap[next]);
			//바꾸는 데이터의 인덱스로 변경
			now = next;
		}
	}
	void pop()
	{
		//백터의 마지막 요소를 뒤로 가져옴
		_heap[0] = _heap.back();
		//맨뒤의 요소 삭제
		_heap.pop_back();
		
		int now =0;
		while (true)
		{
			int left = 2 * now + 1;
			int right = 2*now + 2;
			//자식이 있는지 확인
			if(left>= (int)_heap.size())
				break;
			int next = now;

			//왼쪽과 비교
			if (_predicate(_heap[next], _heap[left]))
				next = left;
			//큰것을 오른쪽과 비교
			if (right < (int)_heap.size()&& _predicate(_heap[next], _heap[right]))
				next = right; 
			//next와 now가 같으면 break
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
	
	
	//template 활용하여서 제작
	PriorityQueue<int,vector<int>,greater<int>> pq;//우선순위 큐 들어온 순서와 상관없이

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




	////stl 활용하여서 제작
	//priority_queue<int,vector<int>,less<int>> pq;//우선순위 큐 들어온 순서와 상관없이	 less 큰것 먼저 출력 출력한다 greater 작은것 먼저 출력
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