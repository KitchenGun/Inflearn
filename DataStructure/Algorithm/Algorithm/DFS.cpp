#include <iostream>
#include <vector>
using namespace std;
//깊이우선탐색 DFS
struct Vertex
{
	int data;
};

vector<Vertex> vertices;

vector<vector<int>> adjacent;

vector<bool> visited;

void CreateGraph()//방문 가능한 간선을 만드는 함수
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// 인접 리스트
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);

	// 인접 행렬
	//adjacent = vector<vector<int>>
	//{
	//	{ 0, 1, 0, 1, 0, 0},
	//	{ 1, 0, 1, 1, 0, 0},
	//	{ 0, 0, 0, 0, 0, 0},
	//	{ 0, 0, 0, 0, 1, 0},
	//	{ 0, 0, 0, 0, 0, 0},
	//	{ 0, 0, 0, 0, 1, 0},
	//};
}


void Dfs(int here)
{
	//1.방문했다
	visited[here] = true;
	//2.노드에 정보를 출력
	cout<<here<<endl;
	//인접 리스트 version
	//3.모든 인접 정점을 순회한다
	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there  = adjacent[here][i];//현재 노드의 연결된 i번째 간선과 연결함
		
		if(visited[there]==false)//연결된 노드에 방문한 적이 없으면 
			Dfs(there);//노드로 방문하도록 재귀함수를 제작함 1번으로 이동
	}

	//인접 행렬 version
	//for (int there = 0; there < 6; there++)
	//{
	//	if(adjacent[here][there]==0)
	//		continue;
	//	if(visited[there]==false)
	//		Dfs(there);
	//}

}


int main()
{
	CreateGraph();
	//시작할때 아무곳도 방문을 하지 않았기 때문에 모든 기본값을 false로 만듬
	visited = vector<bool>(6,false);
	//0번 부터 시작함수
	Dfs(0);


}