#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//넓이 우선 탐색 BFS 큐로 탐색을 한다
vector<vector<int>> adjacent;
vector<bool> discovered;//발견 여부

void CreateGraph()
{
		adjacent.resize(6);

		adjacent[0].push_back(1);
		adjacent[0].push_back(3);
		adjacent[1].push_back(0);
		adjacent[1].push_back(2);
		adjacent[1].push_back(3);
		adjacent[3].push_back(4);
		adjacent[5].push_back(4);

}

void BFS(int here)
{
	//누구에 의해서 발견이 되었는지?
	vector<int> parent(6,-1);
	//시작점에서 얼만큼 떨어져있는지?
	vector<int> distance(6, -1);

	queue<int> q;
	q.push(here);

	discovered[here] = true;//현재 함수의 here를 발견 취급

	parent[here] = here;
	distance[here] = 0;

	while (q.empty() == false)
	{
		here = q.front();
		q.pop();

		cout<<here<<endl;

		for (int there : adjacent[here])
		{
			if(discovered[there])
				continue;
			q.push(there);
			discovered[there] = true;
			//정보 넘기기
			parent[there] = here;//누구를 통해서 방문했는지 검사
			distance[there] = distance[here]+1;//몇번 탐색을 통해서 접근했는지 검사
		}
	}
}



int main()
{
	CreateGraph();
	discovered.resize(6,false);
	BFS(0);

}