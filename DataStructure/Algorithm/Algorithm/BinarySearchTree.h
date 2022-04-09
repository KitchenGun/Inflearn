#pragma once
enum class Color
{
	Red = 0,
	Black = 1,
};

struct Node
{
	Node* parent = nullptr;
	Node* left=nullptr;
	Node* right=nullptr;
	int key = {};
	Color	color = Color::Black; //�⺻�� black
}; 

// Red-Black Tree
// 1) ��� ���� Red or Black
// 2) Root�� Black
// 3) Leaf(NIL)�� Black
// 4) Red ����� �ڽ��� Black (�����ؼ� Red-Red X)
// 5) �� ���κ��� ~ �������� ���� ��ε��� ��� ���� ���� Black
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
	BinarySearchTree();
	~BinarySearchTree();

	void	Print() { Print(root, 10, 0); }
	void	Print(Node* node, int x, int y);

	void Insert(int key);
	void InsertFixup(Node* node);
	void Delete(int key);
	void Delete(Node* node);

	void Replace(Node* u,Node* v);

	Node* Min(Node* node);
	Node* Max(Node* node);
	Node* Next(Node* node);
	Node* Search(Node* node,int key);


	//RedBlack
	void LeftRotate(Node* node);
	void RightRotate(Node* node);

	Node* GetRoot() {return root;}
private:
	Node* nil = nullptr;
	Node* root = nullptr;
};
