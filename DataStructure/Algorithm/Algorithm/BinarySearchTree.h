#pragma once

struct Node
{
	Node* parent = nullptr;
	Node* left=nullptr;
	Node* right=nullptr;
	int key = {};
};

class BinarySearchTree
{
/*Ʈ������
	��
  ��  ��
  ���� �� �� ��
  ���� �� �� ��
  ���� �� �� ��
*/

public:
	void Insert(int key);
	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u,Node* v);

	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);
	Node* Search(Node* node,int key);

	void PrintInOrder(Node* node);//���� ��ȸ
	void PrintInOrder() { PrintInOrder(root); }

	Node* GetRoot() {return root;}
private:
	Node* root = nullptr;
};

