#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//���� �켱 Ž�� BFS ť�� Ž���� �Ѵ�
vector<vector<int>> adjacent;
vector<bool> discovered;//�߰� ����

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
	//������ ���ؼ� �߰��� �Ǿ�����?
	vector<int> parent(6,-1);
	//���������� ��ŭ �������ִ���?
	vector<int> distance(6, -1);

	queue<int> q;
	q.push(here);

	discovered[here] = true;//���� �Լ��� here�� �߰� ���

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
			//���� �ѱ��
			parent[there] = here;//������ ���ؼ� �湮�ߴ��� �˻�
			distance[there] = distance[here]+1;//��� Ž���� ���ؼ� �����ߴ��� �˻�
		}
	}
}



int main()
{
	CreateGraph();
	discovered.resize(6,false);
	BFS(0);

}