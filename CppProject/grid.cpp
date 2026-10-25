#include "config.h"
#include "grid.h"

Grid::Grid(int r, int c)
	: rows(r), cols(c), cellSize(CELL_SIZE)
{
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			nodes.push_back(new Node(i, j, cellSize));
		}

	}
}

Grid::~Grid() {
	for (auto n : nodes)
		delete n;
}

Node* Grid::get(int r, int c) {
	if (r < 0 || c < 0 || r >= rows || c >= cols)
		return nullptr;
	return nodes[r * cols + c];
}

Node* Grid::getNodeAt(float x, float y) {
	for (auto n : nodes) {
		if (n->contains(x, y)) {
			return n;
		}

	}
	return nullptr;
}

std::vector<Node*> Grid::getNeighbors(Node* n) {
	std::vector<Node*> result;
	const int dirs[4][2] = {
		{1,0}, {-1,0}, {0,1}, {0,-1}
	};

	for (auto& d : dirs) {
		Node* neighbor =get(n->row + d[0], n->col + d[1]);
		if (neighbor && neighbor->type != cellType::Obstacle)
			result.push_back(neighbor);
	}
	return result;
}

void Grid::resetSearch() {
	for (auto n: nodes) {
		n->g = n->h = n->f = 0.0f;
		n->parent = nullptr;

		if (n->type == cellType::Open ||
			n->type == cellType::Closed ||
			n->type == cellType::Path)
			n->type = cellType::Empty;
	}

	if (start) start->type = cellType::Start;
	if (goal) goal->type = cellType::Goal;

	
}