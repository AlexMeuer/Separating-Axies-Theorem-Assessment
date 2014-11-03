#ifndef TREE_H
#define TREE_H

//#include <vector>
#include "BouncingThing.h"
//#include "SFML\Window.hpp"

using namespace std;

struct Node {
	Node* parent;
	Vector2u size, position;
	vector<Node*> children;
	vector<BouncingThing*> objects;
};

class QuadTree {
private:
	Node* m_root;
	Vector2u m_windowSize;
	const unsigned int m_ChildrenPerNode;
public:
	QuadTree(RenderWindow* w);
	~QuadTree();

	void addThing(const BouncingThing* thing);

	// Returns false if already 4 child nodes
	bool addNode(Node* parent);
};
#endif