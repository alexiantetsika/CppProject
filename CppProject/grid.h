#pragma once
#include <vector>
#include "node.h"

class Grid {
public:
	int rows, cols;
	float cellSize;

	std::vector<Node*> nodes;

	Node* start = nullptr;
	Node* goal = nullptr;

	Grid(int r, int c);
	~Grid();

	Node* get(int r, int c);

	Node* getNodeAt(float x, float y);

	std::vector<Node*> getNeighbors(Node* n);
	void resetSearch();
};