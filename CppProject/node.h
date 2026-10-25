#pragma once
#include "visualAsset.h"

enum class cellType {
	Empty,
	Obstacle,
	Start,
	Goal,
	Path,
	Open,
	Closed
};

class Node : public visualAsset {
public:
	int row, col;
	float x, y;
	float size;

	cellType type;
	float g = 0.0f;
	float h = 0.0f;
	float f = 0.0f;
	Node* parent = nullptr;


	Node(int r, int c, float size);

	void draw() override;

	bool contains(float px, float py) const;

};
