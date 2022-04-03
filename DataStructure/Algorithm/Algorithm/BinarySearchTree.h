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
/*트리구조
	중
  좌  우
  전위 중 좌 우
  중위 좌 중 우
  후위 좌 우 중
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

	void PrintInOrder(Node* node);//중위 순회
	void PrintInOrder() { PrintInOrder(root); }

	Node* GetRoot() {return root;}
private:
	Node* root = nullptr;
};

