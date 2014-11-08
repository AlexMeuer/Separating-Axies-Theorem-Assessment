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

	// (was originally going to take an arguement for number of children per node,
	// but that's a whole other kettle of fish)
	const unsigned int m_ChildrenPerNode;
public:
	QuadTree(RenderWindow* w);
	~QuadTree();

	// Add a Thing to the tree under whichever node fully contains it.
	void addThing(const BouncingThing* thing);

	// Adds a node to the tree.
	// Returns false if already 4 child nodes.
	bool addNode(Node* parent);
};
#endif