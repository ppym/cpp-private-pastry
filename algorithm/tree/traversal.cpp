#include <iostream>

#define CR std::cout << std::endl;

struct TreeNode {
	int v;
	TreeNode *pLeft;
	TreeNode *pRight;
	
	TreeNode(int val):v(val),pLeft(NULL),pRight(NULL) {}
	~TreeNode(){}
};

void visitNode(TreeNode *node)
{
	if (node) 
		std::cout << node->v << " ";
}

void PreOrder(TreeNode *node)
{
	visitNode(node);
	if (node->pLeft)
		PreOrder(node->pLeft);
	if (node->pRight)
		PreOrder(node->pRight);
}

void PostOrder(TreeNode *node)
{
	if (node->pLeft)
		PostOrder(node->pLeft);
	if (node->pRight)
		PostOrder(node->pRight);
	visitNode(node);
}

void InOrder(TreeNode *node)
{
	if (node->pLeft)
		InOrder(node->pLeft);
	visitNode(node);
	if (node->pRight)
		InOrder(node->pRight);
}

void makeTree(TreeNode **root)
{
	TreeNode *node[5];
	for (int i=0; i<sizeof(node)/sizeof(TreeNode*); i++)
		node[i] = new TreeNode(i);
	node[3]->pLeft = node[1];
	node[3]->pRight = node[4];

	node[1]->pLeft = node[0];
	node[1]->pRight = node[2];

	*root = node[3];
}

int main()
{
	TreeNode *root = NULL;
	makeTree(&root);
	PreOrder(root);
	CR;
	PostOrder(root);
	CR;
	InOrder(root);
	CR;
}

