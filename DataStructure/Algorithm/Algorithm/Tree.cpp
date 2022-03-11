#include <iostream>
#include <vector>
using namespace std;

using NodeRef = shared_ptr<struct Node>;
//shared 포인터로 제작해서 노드 삭제시 자동 관리 되도록 제작

struct Node
{
	Node() {}
	Node(const string& data) : data(data){}

	string data;
	vector<NodeRef> children;
	bool isGetChild = false;
};

NodeRef CreateTree()
{
	NodeRef root = make_shared<Node>("R1 개발실");//노드밑에 노드 추가
	{
		NodeRef node = make_shared<Node>("디자인팀");//노드밑에 노드 추가
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("전투");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("경제");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("스토리");
			node->children.push_back(leaf);
		}
		node->isGetChild = true;
		node = make_shared<Node>("프로그래밍팀");//노드밑에 노드 추가
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("서버");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("클라");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("엔진");
			node->children.push_back(leaf);
		}
		node->isGetChild = true;
		node = make_shared<Node>("아트팀");//노드밑에 노드 추가
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("배경");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("캐릭터");
			node->children.push_back(leaf);
		}
		node->isGetChild = true;
	}
	root->isGetChild=true;
	return root;//맨위에 노드를 반환
}

void PrintTree(NodeRef root,int depth)//재귀함수로 트리를 작게 나눠서 출력 depth를 재귀적으로 늘려서 계층 구조 출력
{
	for (int i = 0; i < depth; i++)
		cout << "-";
	cout << root->data << endl;

	if(root->isGetChild)
	{
		for (NodeRef& child : root->children)
			PrintTree(child, depth + 1);
	}
}

//깊이 : 루트에서 특정 노드에 도달까지 거쳐야하는 간선의 수
//높이 : 가장 깊숙히 있는 노드의 깊이 
//n뭐 사에서 높이를 구하는 손코딩 문제가 나옴
int GetHeight(NodeRef root)
{
	int height =1;
	for (NodeRef& child : root->children)
	{
		height = max(height,GetHeight(child) + 1);//큰 값을 반환  재귀함수를 사용해서
	}
	return height;
}

int main()
{
	NodeRef root=CreateTree();
	PrintTree(root,0);
	cout<<GetHeight(root)<<endl;
}