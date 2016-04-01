// Scott Schumacher, building on a file by Catherine Stringfellow
// File name:	RBTree.cpp
// Description:	implements methods declared in header file; client program interface

#include <iostream>
#include "RBTree.h"
using namespace std;

RBTree::RBTree(){
	root = NULL;
	cursor = NULL;
}

void RBTree::Insert(int x){
	Node * p = NULL;
	if (root == NULL){
		root = new Node();
		root->data = x;
		root->color = 'b';
		root->left = NULL;
		root->right = NULL;
		root->parent = NULL;
		cursor = root;
	}
	else{
		__Insert(p, root, x);
	}
}

int RBTree::Height(){
	return __Height(root);
}

void RBTree::PrintTree(){
	__Print(root);
}

bool RBTree::findItem(int x) {
	bool found = false;
	Node * p;

	//set p to root
	p = root;

	while (!found && (p != NULL)) {
		if (p->data == x)
			found = true;
		else if (x < p->data)
			p = p->left;
		else  if (x > p->data)
			p = p->right;
	}

	//if found, make cursor point to it; might want to do something with it?
	if (found)
		cursor = p;

	return found;
}

void RBTree::deleteItem(int x){
	bool found = findItem(x);

	if (!found)
		cout << "ERROR: Cannot remove item, item is not in tree.\n";
	//item found and cursor is at the node that contains the item
	else {
		__deleteItem();
	}
}

void RBTree::__deleteItem() {
	Node * p;
	Node * q;

	//case 1:  interior node
	if ((cursor->left != NULL) && (cursor->right != NULL)){
		p = cursor;

		//move q to right most node in left subtree
		q = cursor;
		q = q->left;
		while (q->right != NULL)
			q = q->right;

		//copy value in q to the node p
		p->data = q->data;
		cursor = q;
		//delete q which could be a leaf or node that has left subtree
		__deleteItem();

		cursor = p->parent;
	}
	//case 2: has only left subtree
	else if (cursor->left != NULL) {
		p = cursor;

		if (cursor != root) {
			cursor = p->parent;
			cursor->left = p->left;
			p->left->parent = cursor;
		}
		else
		{
			cursor = p->left;
			root = cursor;
			root->parent = NULL;
		}

		delete p;
	}
	//case 3: has only right subtree
	else if (cursor->right != NULL) {
		p = cursor;
		if (cursor != root) {
			cursor = p->parent;
			cursor->right = p->right;
			p->right->parent = cursor;
		}
		else
		{
			cursor = p->right;
			root = cursor;
			root->parent = NULL;
		}
		delete p;
	}
	//case 4: cursor is at leaf, because both left and right are NULL
	else {
		p = cursor;
		if (cursor == root) {
			root = NULL;
			cursor = NULL;
		}
		else {
			cursor = p->parent;
			if (p->parent->left == p)
				p->parent->left = NULL;
			else
				p->parent->right = NULL;
		}
		delete p;
	}

}


void RBTree::__Insert(Node *& parent, Node *&subroot, int data){
	if (subroot == NULL){
		subroot = new Node();
		subroot->data = data;
		subroot->color = 'r';
		subroot->left = NULL;
		subroot->right = NULL;
		subroot->parent = parent;
		cursor = subroot;
	}
	else{
		if (data < subroot->data){
			__Insert(subroot, subroot->left, data);
		}
		else{
			__Insert(subroot, subroot->right, data);
		}
	}
}

void RBTree::__Print(Node *subroot){
	if (subroot == NULL){
		return;
	}
	else{
		//cout << subroot->data << " ";	//Preorder
		__Print(subroot->left);
		cout << subroot->data << " "; //Inorder
		__Print(subroot->right);
		//cout << subroot->data << " "; //Postorder
	}
}

int RBTree::__Height(Node *subroot){
	if (subroot == NULL){
		return 0;
	}
	else{
		int ldepth = __Height(subroot->left);
		int rdepth = __Height(subroot->right);

		if (ldepth > rdepth){
			return 1 + ldepth;
		}
		else{
			return 1 + rdepth;
		}
	}
}

void RBTree::ShiftLeft()
{
	if ((cursor == NULL) || (cursor->left == NULL))
	{
		cout << "ERROR: T's cursor cannot advance left" << endl;
	}
	else
	{
		//move the cursor left
		cursor = cursor->left;
	}
}


void RBTree::ShiftRight()
{
	if ((cursor == NULL) || (cursor->right == NULL))
		cout << "ERROR:  T's cursor cannot advance right" << endl;
	else
	{
		//move the actual cursor
		cursor = cursor->right;
	}
}

void RBTree::ShiftUp()
{
	if ((cursor != NULL) && (cursor != root))
	{
		cursor = cursor->parent;
	}
}

bool RBTree::HasNoChildren()
{
	return ((cursor != NULL) && (cursor->right == NULL) && (cursor->left == NULL));
}

void RBTree::RetrieveData(int & data)
{
	if (cursor != NULL)
	{
		data = cursor->data;
	}
}



