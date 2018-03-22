#include <iostream>

struct TreeNode {
	int data;
	int child_cnt;
	TreeNode *pLeft;
	TreeNode *pRight;
	TreeNode (int d):data(d), child_cnt(0), pLeft(0), pRight(0){}
	void visit() {
		std::cout << data << std::endl;
	}
};

struct BinaryTree {
	TreeNode *root;
	int depth;
	BinaryTree():root(NULL),depth(0){}
	~BinaryTree();
	void add(int data);
	void remove(int data);
	void InOrder(TreeNode*node);
	void BinaryPrint();
	void releaseNode(TreeNode *node);
	void calcDepth();
	int calcDepth(TreeNode *node);
};

void BinaryTree::calcDepth()
{
	depth = calcDepth(root);
}

int BinaryTree::calcDepth(TreeNode *root)
{
	if (!root->pLeft && !root->pRight)
		return 0;
	
	int depth_l = 0, depth_r = 0;
	if (root->pLeft)
		depth_l = calcDepth(root->pLeft);
	if (root->pRight)
		depth_r = calcDepth(root->pRight);

	if (depth_l > depth_r)
		return depth_l+1;
	else
		return depth_r+1;
}

void BinaryTree::releaseNode(TreeNode *node)
{
	if (node) {
		std::cout << "delete " << (long*)node << std::endl;
		TreeNode *l = node->pLeft;
		TreeNode *r = node->pRight;
		delete node;
		releaseNode(l);
		releaseNode(r);
	}
}

BinaryTree::~BinaryTree()
{
	releaseNode(root);
}

void BinaryTree::add(int data)
{
	if (root == NULL) {
		root = new TreeNode(data);
		return;
	}

	TreeNode *n = root;
	TreeNode *n_pre = root;
	while (n) {
		if (data > n->data) {
			n_pre = n;
			n = n->pRight;
		}
		else if (data < n->data) {
			n_pre = n;
			n = n->pLeft;
		}
		else {
			std::cout << "same data" << std::endl;
			return;
		}
	}
	if (n_pre) {
		if (data > n_pre->data) 
			n_pre->pRight = new TreeNode(data);
		else if (data < n_pre->data)
			n_pre->pLeft = new TreeNode(data);
	}

	calcDepth();
}

void BinaryTree::remove(int data)
{
	if (!root)
		return;
	TreeNode *node = root;
	TreeNode *node_parent = NULL;
	bool isLeftTree = false;

	while(node) {
		if (node->data == data)
			break;
		node_parent = node;
		if (node->data > data) {
			node = node->pLeft;
			isLeftTree = true;
		}
		else {
			node = node->pRight;
			isLeftTree = false;
		}
	}

	if (!node_parent) {
		root = NULL;
		delete node;
		return;
	}
	
	if (node) {
		if (node->pLeft == NULL && node->pRight == NULL) {	
			if (isLeftTree) 
				node_parent->pLeft = node->pLeft;
			else 
				node_parent->pRight = node->pLeft;
			delete node;
		}
		else if (node->pLeft != NULL && node->pRight == NULL) {
			if (isLeftTree) 
				node_parent->pLeft = node->pLeft;
			else 
				node_parent->pRight = node->pLeft;
			delete node;
		}
		else if (node->pRight != NULL && node->pLeft == NULL) {
			if (node == root) {
				root = node->pRight;
			}
			else {
			if (isLeftTree)
				node_parent->pLeft = node->pRight;
			else
				node_parent->pRight = node->pRight;
			}
			delete node;
		}
		else {
			TreeNode *min, *pre;
			min = node->pRight;
			pre = node;
			while (min->pLeft) {
				pre = min;
				min = min->pLeft;
			}
			node->data = min->data;
			(pre == node) ? (node->pRight) : (pre->pLeft) = min->pRight;
		}
	}
}

//TreeNode *BinaryTree::del(TreeNode *node)
//{
	//if (
//}

void BinaryTree::InOrder(TreeNode *node)
{
	if (node->pLeft)
		InOrder(node->pLeft);
	node->visit();
	if (node->pRight)
		InOrder(node->pRight);
}

void BinaryTree::BinaryPrint()
{
	InOrder(root);
	
	calcDepth();
	std::cout << "tree depth: " << depth << std::endl;
}

int main()
{
	BinaryTree tree;
	tree.add(20);
	tree.add(10);
	tree.add(11);
	tree.add(25);
	tree.add(30);
	tree.add(17);
	tree.add(15);
	tree.add(22);
	tree.add(33);
	
	tree.BinaryPrint();

	std::cout << "remove root" << std::endl;
	tree.remove(20);
	tree.BinaryPrint();

	std::cout << "remove normal" << std::endl;
	tree.remove(15);
	tree.BinaryPrint();
}

