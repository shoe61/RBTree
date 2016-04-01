// Scott Schumacher, building on a file by Catherine Stringfellow
// File name:	RBTree.h
// Description:	header file; declares class RBTree and the node structure; 
//				creates root and cursor pointers

#include <iostream>
using namespace std;

struct Node{
	int data;
	char color;
	Node *left;
	Node *right;
	Node *parent;
};

class RBTree{

public:
	RBTree();

	void Insert(int x);

	int Height();

	void PrintTree();

	bool findItem(int x);

	void deleteItem(int x);

	void ShiftLeft();
	//precond:  this tree has been created and this tree's cursor not at leaf
	//postcond: this tree's cursor is advanced so that it references the 
	//          left child of the item that this tree's #cursor,
	//          this tree is unChanged otherwise.
	//checks:   this tree's cursor not at leaf

	void ShiftRight();
	//precond:  this tree has been created and this tree's cursor not at leaf
	//postcond: this tree's cursor is advanced so that it references the 
	//          right child of the item that this tree's #cursor,
	//          this tree is unChanged otherwise.
	//checks:   this tree's cursor not at end

	void ShiftUp();
	//precond:  this tree is created and this tree's cursor not at root
	//postcond: this tree's cursor is moved back so that it references the
	//          parent of the item that this tree's #cursor, 
	//          this tree is unChanged otw.
	//checks:   this tree's cursor not referencing root

	bool HasNoChildren();
	//precond:  Tree is created
	//postcond: HasNoChildren = TRUE iff the tree is not empty and the cursor is
	//          pointing at an node that has no children. tree =#tree.
	//checks:   none

	void RetrieveData(int & Item);
	//precond:  this tree is created and this tree's cursor is referencing a node
	//postcond: the value of the item that this tree's cursor references is
	//          returned as the value of Item, this tree = #tree.
	//checks:   this tree's cursor is referencing a node

	
private:
	Node *root;
	Node *cursor;

	void __Insert(Node *& parent, Node *&subroot, int data);
	int __Height(Node *subroot);
	void __Print(Node *subroot);
	void __deleteItem();




};
