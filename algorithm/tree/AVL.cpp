#include <iostream>
#include <assert.h>
#include <deque>

struct AVLNode {
	int data;
	int dp; //左子树的高度-右子树的高度
	int height; //
	AVLNode *parent;
	AVLNode *left;
	AVLNode *right;
	AVLNode(int d, AVLNode *p):data(d),dp(0), height(0), parent(p), left(NULL),right(NULL){}
	void visit() {
		std::cout << data << std::endl;
	}
};

struct AVLTree {
	AVLNode *root;
	int depth;
	AVLTree():root(NULL),depth(0){}
	~AVLTree();
	void del(AVLNode *node);
	
	AVLNode *add_inline(AVLNode* root, int data);
	void add(int data);
	AVLNode *balance(AVLNode *node);
	AVLNode *find_broken_balance(AVLNode *node);
	AVLNode *R_rotate(AVLNode *node);
	AVLNode *L_rotate(AVLNode *node);
	void preOrder(AVLNode *node);
	void inOrder(AVLNode *node);
	void print();
	void printSort();
	void printTree();
	void printdp();
	void calcDepth();
	int calcDepth(AVLNode*node);
};

void AVLTree::calcDepth()
{
	depth = calcDepth(root);
}

int AVLTree::calcDepth(AVLNode *root)
{
	if (!root->left && !root->right)
		return 0;
	
	int depth_l = 0, depth_r = 0;
	if (root->left)
		depth_l = calcDepth(root->left);
	if (root->right)
		depth_r = calcDepth(root->right);

	if (depth_l > depth_r)
		return depth_l+1;
	else
		return depth_r+1;
}

void AVLTree::preOrder(AVLNode *node)
{
	if (node) {
		node->visit();
		preOrder(node->left);
		preOrder(node->right);
	}
}

void AVLTree::inOrder(AVLNode *node)
{
	if (node) {
		inOrder(node->left);
		node->visit();
		inOrder(node->right);
	}
}


void AVLTree::print()
{
	preOrder(root);
}

void AVLTree::printSort()
{
	inOrder(root);
}

void AVLTree::printTree()
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
	std::deque<AVLNode*> list;
	list.push_back(root);
	AVLNode *curr;

	while(!list.empty()) {
		curr = list.front();
		list.pop_front();
		if (curr)
			std::cout << curr->data << " ";
		else {
			std::cout << "#" << " ";
			continue;
		}
		
		if (curr->left) 
			list.push_back(curr->left);
		else 
			list.push_back(0);

		if (curr->right) 
			list.push_back(curr->right);
		else
			list.push_back(0);
	}
	std::cout << std::endl;

}

void AVLTree::printdp()
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
	std::deque<AVLNode*> list;
	list.push_back(root);
	AVLNode *curr;

	while(!list.empty()) {
		curr = list.front();
		list.pop_front();
		if (curr)
			std::cout << curr->dp << " ";
		else {
			std::cout << "#" << " ";
			continue;
		}
		
		if (curr->left) 
			list.push_back(curr->left);
		else 
			list.push_back(0);

		if (curr->right) 
			list.push_back(curr->right);
		else
			list.push_back(0);
	}
	std::cout << std::endl;
}

void AVLTree::del(AVLNode* node)
{
	if (!node) return;
//	std::cout << "delete " << (long*)node << std::endl;
	delete node;
	if (node->left)
		del(node->left);
	if (node->right)
		del(node->right);
}

AVLTree::~AVLTree()
{
	if (root)
		del(root);
}

AVLNode *AVLTree::R_rotate(AVLNode *node)
{
	AVLNode *new_ = node->left;
	node->left = new_->right;
	new_->right = node;
	return new_;
}

AVLNode *AVLTree::L_rotate(AVLNode *node)
{
	AVLNode *new_ = node->right;
	node->right = new_->left;
	new_->left = node;
	return new_;
}

AVLNode *AVLTree::balance(AVLNode *node)
{
	std::cout << "balance " << std::endl;
	if (!node) return NULL;

	assert(node->dp == 2 || node->dp == -2); //没破坏平衡不要调用balance

	//首先，每次AVL树都要满足left_dp - right_dp < 2,
	//其次，每次只能加一个节点，即left_dp+1 或者 right_dp+1 （也可能加新节点不会增加高度,此时不会破坏原本AVL的平衡状态）	
	//所以出现left_dp - right_dp == 2只能是left_dp +1，
	//出现left_dp - right_dp == -2 只能是right_dp +1.
	if (node->dp == 2) { //说明加入的新节点是加在左子树，如果是加在右子树，说明是右子树的高度增加了1，那左子树减去右子树要出现2的值，左子树得加高度 (left_dp + 1) - (right_dp) = 2
		assert(node->left->dp == 1 || node->left->dp == -1); //如果左子树的dp为0,说明左子树加入新节点之后左右高度是一样的，那在没加新节点之前就违反了AVL的平衡
		std::cout << "balance child node left dp " << node->left->dp << std::endl;
		if (node->left->dp == 1) {
			node->dp = 0; //右旋之后都恢复左右两边0平衡
			node->left->dp = 0;
			return R_rotate(node);
		}
		else {
			node->left->right->dp = 0; //左孩子的右孩子将成为顶点
			if (node->left->right->left) { //新加入的节点出现在左子树的最左，最终将被left的节点接管为右孩子
				node->left->dp = 0;
				node->dp = -1;
			}
			else {
				node->left->dp = 1;
				node->dp = 0;
			}
				
			node->left = L_rotate(node->left); //“左右”的情况，打破平衡的新节点添加在node的左子树的右子树上
			std::cout << "l_rorate node " << node->left->data << std::endl;
			printTree();
			return R_rotate(node);
		}
	}
	else { //dp==-2 说明加入的新节点是加在右子树，如果是加在左子树，说明是左子树的高度增加了1，那左子树减去右子树要出现-2的值，右子树得加高度 (left_dp ) - (right_dp +1) = -2
		assert(node->right->dp == 1 || node->right->dp == -1); //如果右子树的dp为0,说明右子树加入新节点之后左右高度是一样的，那在没加新节点之前就违反了AVL的平衡
		if (node->right->dp == -1) { //“右右”的情况，打破平衡的新节点添加在node的右子树的右子树上
			node->dp = 0; //左旋之后都恢复左右两边0平衡
			node->right->dp = 0;
			return L_rotate(node);
		}
		else {
			node->right->left->dp = 0; //成为顶点
			if (node->right->left->right) { //最终新加入的节点被node的右孩子接管
				node->right->dp = 0;
				node->dp = 1;
			}
			else { //新加入的节点被node接管
				node->right->dp = -1;
				node->dp = 0;
			}
			node->right = R_rotate(node->right); //“右左”的情况，打破平衡的新节点添加在node的右子树的左子树上
			return L_rotate(node);
		}
	}
}

AVLNode *AVLTree::add_inline(AVLNode* root, int data)
{
	AVLNode *node = root;
	if (root->data == data)
		return NULL; 

	if (data < root->data)
	{
		if (!root->left) {
			root->left = new AVLNode(data, root);
			return root->left;
		}
		else {
			return add_inline(root->left, data);
		}
	}
	else {
		if (!root->right) {
			root->right = new AVLNode(data, root);
			return root->right;
		}
		else
			return add_inline(root->right, data);
	}
}

AVLNode *AVLTree::find_broken_balance(AVLNode *node)
{
	if (!node) return NULL;
	AVLNode *child = node;
	AVLNode *parent = node->parent;
	if (parent && parent->left && parent->right) { //说明加入新节点之前，其父节点已经有一条边且没有打破平衡，那多一条边也不会打破平衡
		parent->dp = 0;
		return NULL;
	}

	while (parent) {
		if (parent->left == child)
			parent->dp++;
		else
			parent->dp--;
		if (parent->dp == 2 || parent->dp == -2)
			break;
		child = parent;
		parent = parent->parent;
	}

	if (parent)
		std::cout << "find_broken_balance=" << parent << " data=" <<  parent->data << std::endl;
	return parent;
}

void AVLTree::add(int data)
{
	if (!root) {
		root = new AVLNode(data, NULL);
		return;
	}
	AVLNode *node = add_inline(root, data);
	//std::cout << "add node=" << node << " data=" << node->data << std::endl;
	
	printTree();
	AVLNode *broken_node = find_broken_balance(node);
	printTree();
	std::cout << "add broken_node " << broken_node << " parent " << (broken_node ? broken_node->parent : NULL) << std::endl;
	if (broken_node) {
		if (broken_node->parent) {
			if (broken_node->parent->left == broken_node) //位于左子树
				broken_node->parent->left = balance(broken_node);
			else
				broken_node->parent->right = balance(broken_node);
		}
		else
			root = balance(broken_node);
	}
	//std::cout << "broken_node=" << broken_node << std::endl;
	//std::cout << "root=" << root << std::endl;
}


#define JUST_R_ROTATE 0
#define JUST_L_ROTATE 0
#define L_R_ROTATE 1
#define R_L_ROTATE 0
void test_r_rotate()
{
	std::cout << "r_rotate============" << std::endl;
	AVLTree tree;
	tree.add(10);
	tree.add(9);
	tree.add(8);
	std::cout << "AVL tree print " << std::endl;
	tree.printTree();
	tree.printdp();
	//tree.printSort();
}

void test_l_rotate()
{
	std::cout << "l_rotate============" << std::endl;
	AVLTree tree;
	tree.add(10);
	tree.add(11);
	tree.add(12);
	std::cout << "AVL tree print " << std::endl;
	tree.printTree();
	tree.printdp();
	//tree.printSort();

}

void test_l_r_rotate()
{
	std::cout << "l_r_rotate =============" << std::endl;
	AVLTree tree;
	tree.add(20);	
	tree.add(10);
	tree.add(25);
	tree.add(22);
	tree.add(7);
	tree.add(15);
	tree.add(5);
	tree.add(8);
	tree.add(9);
	std::cout << "AVL tree print " << std::endl;
	tree.printTree();
	tree.printdp();
}

void test_l_r_rotate2()
{
	std::cout << "l_r_rotate 2 =============" << std::endl;
	AVLTree tree;
	tree.add(20);	
	tree.add(10);
	tree.add(25);
	tree.add(15);
	tree.add(9);
	tree.add(11);
	std::cout << "AVL tree print " << std::endl;
	tree.printTree();
	tree.printdp();
}

void test_r_l_rotate()
{
	std::cout << "r_l_rotate =============" << std::endl;
	AVLTree tree;
	tree.add(20);
	tree.add(10);
	tree.add(30);
	tree.add(40);
	tree.add(25);
	tree.add(22);
	std::cout << "AVL tree print " << std::endl;
	tree.printTree();
	tree.printdp();
}

void test_r_l_rotate2()
{
	std::cout << "r_l_rotate =============" << std::endl;
	AVLTree tree;
	tree.add(20);
	tree.add(10);
	tree.add(30);
	tree.add(40);
	tree.add(25);
	tree.add(27);
	std::cout << "AVL tree print " << std::endl;
	tree.printTree();
	tree.printdp();
}
int main()
{
	test_r_rotate();
	test_l_rotate();
	test_l_r_rotate();
	test_l_r_rotate2();
	test_r_l_rotate();
	test_r_l_rotate2();
}

