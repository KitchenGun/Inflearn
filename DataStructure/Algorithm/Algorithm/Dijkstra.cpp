#include <iostream>
#include <vector>
#include <list>

using namespace std;

//기존 Bfs와의 차이는 노드간의 이동 비용을 포함하여 계산하는 것이다.

struct Vertex 
{
	int data;
};

vector<Vertex> vertices;
vector<vector<int>> adjacent;

void CreateGraph()
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6,vector<int>(6,-1));//2차원 배열 생성

	adjacent[0][1] = 15;
	adjacent[0][3] = 35;
	adjacent[1][0] = 15;
	adjacent[1][2] = 5;
	adjacent[1][3] = 10;
	adjacent[3][4] = 5;
	adjacent[5][4] = 5;
}

void Dijkstra(int here)
{
	struct VertexCost
	{
		int vertex;
		int cost;
	};
	list<VertexCost> discovered;//발견목록
	vector<int> best(6,INT32_MAX);	//각 정점별 발견한 최소 거리
	vector<int> parent(6,-1);

	discovered.push_back(VertexCost{here,0});//시작 지점 집어 넣기
	best[here]=0;//시작점 초기화
	parent[here] = here;


	while (discovered.empty() == false)
	{//제일 좋은 후보를 찾는다
		list<VertexCost>::iterator bestIt;
		int bestCost = INT32_MAX;

		for (auto it = discovered.begin();it!=discovered.end();it++)
		{
			if (bestCost > it->cost)//cost 와 bestcost를 비교 하여 
			{//최적을 찾아내면
				bestCost = it->cost;
				bestIt = it;
			}
		}
	
		int cost = bestIt->cost;
		here = bestIt->vertex;
		//최적의 데이터를 지운다
		discovered.erase(bestIt);
		//방문? 더 짧은 경로를 뒤늦게 찾았다면 스킵
		if (best[here] < cost)
			continue;
		//방문
		for (int there = 0; there < 6; there++)
		{
			//연결되지 않았으면 스킵
			if (adjacent[here][there] == -1)
				continue;
			//더 좋은 경로를 과거에 찾았으면 스킵
			int nextCost = best[here]+adjacent[here][there];
			if(nextCost>=best[there])
				continue;
			discovered.push_back(VertexCost{there,nextCost});
			best[there] = nextCost;
			parent[there] = here;
			//같은 번호의 여러cost를 제작해서 추가한다
			//cost {3,35} {3,25} 이런식으로 추가가 된다
		}
	}
	int a;
}

int main()
{
	CreateGraph();
	Dijkstra(0);

}