#include <iostream>
#include <vector>
using namespace std;
//���̿켱Ž�� DFS
struct Vertex
{
	int data;
};

vector<Vertex> vertices;

vector<vector<int>> adjacent;

vector<bool> visited;

void CreateGraph()//�湮 ������ ������ ����� �Լ�
{
	vertices.resize(6);
	adjacent = vector<vector<int>>(6);

	// ���� ����Ʈ
	adjacent[0].push_back(1);
	adjacent[0].push_back(3);
	adjacent[1].push_back(0);
	adjacent[1].push_back(2);
	adjacent[1].push_back(3);
	adjacent[3].push_back(4);
	adjacent[5].push_back(4);

	// ���� ���
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
	//1.�湮�ߴ�
	visited[here] = true;
	//2.��忡 ������ ���
	cout<<here<<endl;
	//���� ����Ʈ version
	//3.��� ���� ������ ��ȸ�Ѵ�
	for (int i = 0; i < adjacent[here].size(); i++)
	{
		int there  = adjacent[here][i];//���� ����� ����� i��° ������ ������
		
		if(visited[there]==false)//����� ��忡 �湮�� ���� ������ 
			Dfs(there);//���� �湮�ϵ��� ����Լ��� ������ 1������ �̵�
	}

	//���� ��� version
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
	//�����Ҷ� �ƹ����� �湮�� ���� �ʾұ� ������ ��� �⺻���� false�� ����
	visited = vector<bool>(6,false);
	//0�� ���� �����Լ�
	Dfs(0);


}