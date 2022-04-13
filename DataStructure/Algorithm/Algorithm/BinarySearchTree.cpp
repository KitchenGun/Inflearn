 #include "BinarySearchTree.h"
#include <iostream>
#include <windows.h>
#include <thread>
using namespace std;


enum class ConsoleColor
{
	BLACK = 0,
	RED = FOREGROUND_RED,
	GREEN = FOREGROUND_GREEN,
	BLUE = FOREGROUND_BLUE,
	YELLOW = RED | GREEN,
	WHITE = RED | GREEN | BLUE,
};

void SetCursorColor(ConsoleColor color)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	::SetConsoleTextAttribute(output, static_cast<SHORT>(color));
}

void SetCursorPosition(int x, int y)
{
	HANDLE output = ::GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	::SetConsoleCursorPosition(output, pos);
}


int main()
{
	BinarySearchTree bst;

	bst.Insert(30);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(10);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(20);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(25);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(40);
	bst.Print();
	this_thread::sleep_for(1s);
	bst.Insert(50);
	bst.Print();
	this_thread::sleep_for(1s);
}

BinarySearchTree::BinarySearchTree()
{
	nil = new Node();//black
	root = nil;

}

BinarySearchTree::~BinarySearchTree()
{
	delete nil;
}

void BinarySearchTree::Print(Node* node, int x, int y)
{
	if (node == nil)
		return;

	SetCursorPosition(x, y);

	if (node->color == Color::Black)
		SetCursorColor(ConsoleColor::BLUE);
	else
		SetCursorColor(ConsoleColor::RED);

	cout << node->key;
	Print(node->left, x - (5 / (y + 1)), y + 1);
	Print(node->right, x + (5 / (y + 1)), y + 1);

	SetCursorColor(ConsoleColor::WHITE);
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();

	newNode->key = key;

	Node* node = root;
	Node* parent = nil;

	//nil이 아닌동안 실행
	while (node!=nil)
	{
		parent = node;
		if(key<node->key)
			node = node->left;
		else
			node = node->right;
	}
	newNode->parent = parent;

	if(parent==nil)
		root = newNode;
	else if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;

	//레드블랙 트리에 맞는지 검사
	newNode->left = nil;
	newNode->right = nil;
	newNode->color = Color::Red;
	
	InsertFixup(newNode);
}

void BinarySearchTree::InsertFixup(Node* node)
{//레드블랙 트리 구조 규칙에 맞지 않으면 수정
	//rule 1 parent = red || uncle = red    ->p = black, uncle = black, pp= red
	//아래 상황인 경우 1번 케이스 실행
	//	     [pp(B)]
	//	[p(R)]	       [u(R)]
	//	  [n(R)]
	//rule 2 parent = red || uncle = black(triangle)
	//아래 상황인 경우 2번 케이스 실행			->회전함수를 돌려서 rule3로 변경
	//	     [pp(B)]
	//	[p(R)]	       [u(B)]
	//	  [n(R)]
	//rule 3 parent = red || uncle = black(list) -> 색상변경 + 회전
	//아래 상황인 경우 3번 케이스 실행
	//	     [pp(B)]
	//	[p(R)]	       [u(B)]
	//[n(R)]
	
	while (node->parent->color == Color::Red)
	{
		if (node->parent == node->parent->parent->left)
		{
			Node* uncle = node->parent->parent->right;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black; // p
				uncle->color = Color::Black; // u
				node->parent->parent->color = Color::Red; // pp
				node = node->parent->parent;
			}
			else
			{
				//       [pp(B)]
				//   [p(R)]     [u(B)]
				//      [n(R)]

				//        [pp(B)]
				//      [p(R)]  [u(B)]
				//   [n(R)]   

				if (node == node->parent->right) // Triangle 타입
				{
					node = node->parent;
					LeftRotate(node);
				}

				// List 타입

				//        [pp(R)]
				//      [p(B)]  [u(B)]
				//   [n(R)]  

				//       [p(B)]  
				//   [n(R)]   [pp(R)]
				//					[u(B)]
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				RightRotate(node->parent->parent);
			}
		}
		else
		{
			Node* uncle = node->parent->parent->left;
			if (uncle->color == Color::Red)
			{
				node->parent->color = Color::Black; // p
				uncle->color = Color::Black; // u
				node->parent->parent->color = Color::Red; // pp
				node = node->parent->parent;
			}
			else
			{
				if (node == node->parent->left) // Triangle 타입
				{
					node = node->parent;
					RightRotate(node);
				}

				// List 타입

				//					 [p(B)]    
				//			  [pp(R)]      [n(R)]  
				//      [u(B)] 
				node->parent->color = Color::Black;
				node->parent->parent->color = Color::Red;
				LeftRotate(node->parent->parent);
			}
		}
	}

	root->color = Color::Black;
}

void BinarySearchTree::Delete(int key)
{
	Node* deleteNode = Search(root,key);
	Delete(deleteNode);

}

void BinarySearchTree::Delete(Node* node)
{
	if (node == nullptr)
		return;

	if (node->left == nullptr)
		Replace(node, node->right);
	else if (node->right == nullptr)
		Replace(node, node->left);
	else
	{
		// 다음 데이터 찾기
		Node* next = Next(node);
		node->key = next->key;
		Delete(next);
	}
}

void BinarySearchTree::Replace(Node* u, Node* v)
{//u서브 트리를 v 서브트리로 교체

	if(u->parent==nullptr)
		root = v;
	else if(u==u->parent->left)
		u->parent->left = v;
	else
		u->parent->right = v;

	if(v)
		v->parent = u->parent; 

	delete u;
}

Node* BinarySearchTree::Min(Node* node)
{
	while (node->left != nil)
		node = node->left;

	return node;
}

Node* BinarySearchTree::Max(Node* node)
{
	while (node->right != nil)
		node = node->right;

	return node;
}

Node* BinarySearchTree::Next(Node* node)
{
	if (node->right != nil)
		return Min(node->right);

	Node* parent = node->parent;

	while (parent != nil && node == parent->right)
	{
		node = parent;
		parent = parent->parent;
	}

	return parent;
}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if(node==nil||node->key==key)
	return node;

	if(key < node->key)
		return Search(node->left,key);
	else 
		return Search(node->right, key);
}


//		[y]
//	 [x]   [3]
// [1] [2]
//->right rotate  ->    ->left rotate
//	 [x] 			    	  [y]
// [1] [y]			       [x]   [3]
//	  [2][3]		     [1] [2]
void BinarySearchTree::LeftRotate(Node* x)
{
	Node* y = x->right;
	x->right = y->left;//[2]를 옮기는 과정
	if(y->left!=nil)
		y->left->parent = x;
	y->parent = x->parent;

	if(x->parent == nil)
		root = y;
	else if(x==x->parent->left)
		x->parent->left=y;
	else
		x->parent->right=y;

	y->left = x;
	x->parent = y;
}

void BinarySearchTree::RightRotate(Node* y)
{
	Node* x = y->left;

	y->left = x->right; // [2];

	if (x->right != nil)
		x->right->parent = y;

	x->parent = y->parent;

	if (y->parent == nil)
		root = x;
	else if (y == y->parent->left)
		y->parent->left = x;
	else
		y->parent->right = x;

	x->right = y;
	y->parent = x;
}

