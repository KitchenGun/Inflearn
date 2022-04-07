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
	Color	color = Color::Black; //기본값 black
}; 

// Red-Black Tree
// 1) 모든 노드는 Red or Black
// 2) Root는 Black
// 3) Leaf(NIL)는 Black
// 4) Red 노드의 자식은 Black (연속해서 Red-Red X)
// 5) 각 노드로부터 ~ 리프까지 가는 경로들은 모두 같은 수의 Black
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

