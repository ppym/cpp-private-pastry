#include <iostream>
#include <set>
#include <deque>

using namespace std;

struct Node{
	int point;
	std::set<Node*> next;

	Node (int p=0) : point(p) {}
	void AddNext(Node *node) {
		next.insert(node);
	}
};

void initRouteMap(Node **root, int *end)
{
	Node *nodes = new Node[6];
	for (int i=0; i<6; i++) {
		nodes[i].point = i;
	}
	*root = &nodes[0];
	
	nodes[0].AddNext(&nodes[1]);
	nodes[0].AddNext(&nodes[2]);

	nodes[1].AddNext(&nodes[3]);
	nodes[1].AddNext(&nodes[4]);

	nodes[2].AddNext(&nodes[3]);
	nodes[2].AddNext(&nodes[5]);

	//nodes[3].AddNext(&nodes[0]);

	nodes[5].AddNext(&nodes[4]);
	*end = 4;
}

void printRouteMap(Node *node)
{
	std::cout << node->point;
	for (auto subNode : node->next) {
		std::cout << "-->";
		printRouteMap(subNode);
		std::cout << "\n";
	}
}

void printRoute(std::deque<Node *> &queue)
{
	std::cout << "find one route: \t";
	for (std::deque<Node *>::iterator it = queue.begin(); it != queue.end(); ) {
		std::cout << (*it)->point;
		if (++it !=queue.end())
			std::cout << "->" ;
	}
	std::cout << "\n";
}

void BFS(std::deque<Node*> &queue, Node *node, int end)
{
	queue.push_back(node);
	for (auto subNode : node->next) {
		if (subNode->point == end) {
			queue.push_back(subNode);
			printRoute(queue);
			queue.pop_back();
		}
	}

	for (auto subNode : node->next) {
		BFS(queue, subNode, end);
	}
	queue.pop_back();
}

int main()
{
	Node *root;
	int end;
	initRouteMap(&root, &end);
	printRouteMap(root);
	std::deque<Node *> queue;
	BFS(queue, root, end);
}

