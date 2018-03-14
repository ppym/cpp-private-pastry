#include <iostream>
#include <set>
#include <deque>

using namespace std;

struct Node{
	std::string name;
	std::set<Node*> next;

	Node (std::string p="") : name(p) {}
	void AddNext(Node *node) {
		next.insert(node);
	}
};

void initRouteMap(Node **root, std::string *end)
{
	Node *nodes = new Node[6];
	nodes[0].name = "CAB";
	nodes[1].name = "CAR";
	nodes[2].name = "CAT";
	nodes[3].name = "MAT";
	nodes[4].name = "BAT";
	nodes[5].name = "BAR";
	
	*root = &nodes[0];
	nodes[0].AddNext(&nodes[1]);
	nodes[0].AddNext(&nodes[2]);

	nodes[1].AddNext(&nodes[2]);
	nodes[1].AddNext(&nodes[5]);

	nodes[2].AddNext(&nodes[3]);
	nodes[2].AddNext(&nodes[4]);

	nodes[3].AddNext(&nodes[4]);

	nodes[5].AddNext(&nodes[4]);
	nodes[5].AddNext(&nodes[1]);
	*end = "BAT";
}

void printRouteMap(Node *node)
{
	std::cout << node->name;
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
		std::cout << (*it)->name;
		if (++it !=queue.end())
			std::cout << "->" ;
	}
	std::cout << "\n";
}

bool isLoopQueue(std::deque<Node*> &queue, Node *node)
{
	for (std::deque<Node *>::iterator it = queue.begin(); it != queue.end(); it++)
		if(*it == node)
			return true;
	return false;
}

void BFS(std::deque<Node*> &queue, Node *node, std::string end)
{
	if (isLoopQueue(queue, node)) 
		return;

	queue.push_back(node);
	for (auto subNode : node->next) {
		if (subNode->name == end) {
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
	std::string end;
	initRouteMap(&root, &end);
//	printRouteMap(root);
	std::deque<Node *> queue;
	BFS(queue, root, end);
}

