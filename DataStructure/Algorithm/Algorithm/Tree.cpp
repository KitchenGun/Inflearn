#include <iostream>
#include <vector>
using namespace std;

using NodeRef = shared_ptr<struct Node>;
//shared �����ͷ� �����ؼ� ��� ������ �ڵ� ���� �ǵ��� ����

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
	NodeRef root = make_shared<Node>("R1 ���߽�");//���ؿ� ��� �߰�
	{
		NodeRef node = make_shared<Node>("��������");//���ؿ� ��� �߰�
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("����");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("����");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("���丮");
			node->children.push_back(leaf);
		}
		node->isGetChild = true;
		node = make_shared<Node>("���α׷�����");//���ؿ� ��� �߰�
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("����");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("Ŭ��");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("����");
			node->children.push_back(leaf);
		}
		node->isGetChild = true;
		node = make_shared<Node>("��Ʈ��");//���ؿ� ��� �߰�
		root->children.push_back(node);
		{
			NodeRef leaf = make_shared<Node>("���");
			node->children.push_back(leaf);
		}
		{
			NodeRef leaf = make_shared<Node>("ĳ����");
			node->children.push_back(leaf);
		}
		node->isGetChild = true;
	}
	root->isGetChild=true;
	return root;//������ ��带 ��ȯ
}

void PrintTree(NodeRef root,int depth)//����Լ��� Ʈ���� �۰� ������ ��� depth�� ��������� �÷��� ���� ���� ���
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

//���� : ��Ʈ���� Ư�� ��忡 ���ޱ��� ���ľ��ϴ� ������ ��
//���� : ���� ����� �ִ� ����� ���� 
//n�� �翡�� ���̸� ���ϴ� ���ڵ� ������ ����
int GetHeight(NodeRef root)
{
	int height =1;
	for (NodeRef& child : root->children)
	{
		height = max(height,GetHeight(child) + 1);//ū ���� ��ȯ  ����Լ��� ����ؼ�
	}
	return height;
}

int main()
{
	NodeRef root=CreateTree();
	PrintTree(root,0);
	cout<<GetHeight(root)<<endl;
}