#include <iostream>
#include <cmath>
#include <deque>

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
	void printTree();
	void releaseNode(TreeNode *node);
	void calcDepth();
	int calcDepth(TreeNode *node);
	TreeNode *del(TreeNode *node);
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

void BinaryTree::printTree()
{
	if (!root) {
		std::cout << "Tree empty " << std::endl;
		return;
	}
#if 0 //wrong 
	if (depth == 0) {
		std::cout << root->data << std::endl;
		return;
	}

	int len = 3*pow(2,depth-1) + pow(2,depth-1) - 1;
	int suffix, gap, count;
	TreeNode *node = root;
	for (int i=0; i<depth; i++) {
		count = pow(2,i);
		gap = len/count;
		suffix = gap>>1;

		for (int j=0; j<suffix; j++)
			std::cout << " ";

		for (j=0; j<count; j++) {
		}

		for (int j=0; j<suffix; j++)
			std::cout << " ";
		std::cout << std::endl;
	}
#endif
	std::deque<TreeNode*> list;
	list.push_back(root);
	TreeNode *curr;

	while(!list.empty()) {
		curr = list.front();
		list.pop_front();
		if (curr)
			std::cout << curr->data << " ";
		else {
			std::cout << "#" << " ";
			continue;
		}
		
		if (curr->pLeft) 
			list.push_back(curr->pLeft);
		else 
			list.push_back(0);

		if (curr->pRight) 
			list.push_back(curr->pRight);
		else
			list.push_back(0);
	}
	std::cout << std::endl;

}

void BinaryTree::releaseNode(TreeNode *node)
{
	if (node) {
		//std::cout << "delete " << (long*)node << std::endl;
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

TreeNode *BinaryTree::del(TreeNode *node)
{
	TreeNode *ret = NULL;
	if (!node->pLeft && !node->pRight) {
		delete node;
	}
	else if (!node->pLeft && node->pRight) {
		ret = node->pRight;
		delete node;
	}
	else if (!node->pRight && node->pLeft) {
		ret = node->pLeft;
		delete node;
	}
	else {
		//find min data in node's Right subtree
		TreeNode *min = node->pRight;
		TreeNode *pre = node;
		while(min->pLeft) {
			pre = min;
			min = min->pLeft;
		}
		node->data = min->data;
		if (pre != node) {
			pre->pLeft = min->pRight;
		}
		else {
			pre->pRight = min->pRight;
		}
		delete min;
		ret = node;
	}

	return ret;
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

	if (!node) return;

	if (!node_parent) { //root节点
		root = del(root);
		return;
	}

	if (isLeftTree) {
		node_parent->pLeft = del(node);
	}
	else {
		node_parent->pRight = del(node);
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
	
	//tree.BinaryPrint();

	std::cout << "remove root" << std::endl;
	tree.remove(20);
	//tree.BinaryPrint();

	std::cout << "remove normal" << std::endl;
	tree.remove(15);
	tree.BinaryPrint();
	tree.printTree();
}

