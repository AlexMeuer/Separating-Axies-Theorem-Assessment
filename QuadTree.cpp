#include "Quadtree.h"

QuadTree::QuadTree(RenderWindow* w) : m_windowSize(w->getSize()), m_ChildrenPerNode(4) {
	m_root = new Node();
	m_root->parent = NULL;
}

void QuadTree::addThing(const BouncingThing* thing) {
	Node* node = m_root;

}

// Returns false if already 4 child nodes
bool QuadTree::addNode(Node* parent) {
	if( parent->children.size() >= m_ChildrenPerNode ) {
		return false;
	}
	else {
		parent->children.push_back(new Node());
		//TODO: set up child node variables
	}
}