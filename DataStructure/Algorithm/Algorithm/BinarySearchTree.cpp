#include "BinarySearchTree.h"
#include <iostream>

using namespace std;


int main()
{
	BinarySearchTree bst;

	bst.Insert(20);
	bst.Insert(10);
	bst.Insert(30);
	bst.Insert(40);
	bst.Insert(50);
	bst.PrintInOrder();


	Node* next = bst.Next(bst.Search(bst.GetRoot(),50));
	cout<<(next!=nullptr?next->key:0)<<endl;

	cout<<bst.Max(bst.GetRoot())->key<<endl;
}

void BinarySearchTree::Insert(int key)
{
	Node* newNode = new Node();

	newNode->key = key;

	if (root == nullptr)
	{
		root = newNode;
		return;
	}
	Node* node = root;
	Node* parent = nullptr;
	while (node)
	{
		parent = node;
		if(key<node->key)
			node = node->left;
		else
			node = node->right;
	}
	newNode->parent = parent;

	if (key < parent->key)
		parent->left = newNode;
	else
		parent->right = newNode;
}

Node* BinarySearchTree::Min(Node* node)
{
	if(node->left==nullptr)
		return node;

	return Min(node->left);
}

Node* BinarySearchTree::Max(Node* node)
{
	if (node->right == nullptr)
		return node;

	return Max(node->right);
}

Node* BinarySearchTree::Next(Node* node)
{
	if(node->right!=nullptr)
		return Min(node->right);
	else
		return nullptr;

	Node* parent = node->parent;

	while (parent && parent->right==node)
	{
		node = parent;
		parent = parent->parent;
	}
		
	return parent;

}

Node* BinarySearchTree::Search(Node* node, int key)
{
	if(node==nullptr||node->key==key)
	return node;

	if(key < node->key)
		return Search(node->left,key);
	else 
		return Search(node->right, key);
}

void BinarySearchTree::PrintInOrder(Node* node)
{
	//전위 중 좌 우
	if(node==nullptr)
		return;

	cout<<node->key<<endl;

	PrintInOrder(node->left);
	PrintInOrder(node->right);
}
