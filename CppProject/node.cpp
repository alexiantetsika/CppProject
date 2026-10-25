#include "graphics.h"
#include "node.h"
#include "config.h"

Node::Node(int r, int c, float s)
	: row(r), col(c), size(s), type(cellType::Empty)
{
	x = c * size + size / 2.0f;
	y = r * size + size / 2.0f;
}

void Node::draw() {
	graphics::Brush br;

	switch (type)
	{
	case cellType::Empty:
		br.fill_color[0] = 0.9f;
		br.fill_color[1] = 0.9f;
		br.fill_color[2] = 0.9f;
		break;
	case cellType::Obstacle:
		br.fill_color[0] = 0.2f;
		br.fill_color[1] = 0.2f;
		br.fill_color[2] = 0.2f;
		break;
	case cellType::Start:
		br.fill_color[0] = 0.2f;
		br.fill_color[1] = 0.8f;
		br.fill_color[2] = 0.2f;
		break;
	case cellType::Goal:
		br.fill_color[0] = 0.8f;
		br.fill_color[1] = 0.2f;
		br.fill_color[2] = 0.2f;
		break;
	case cellType::Open:
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 0.6f;
		br.fill_color[2] = 1.0f;
		break;
	case cellType::Closed:
		br.fill_color[0] = 0.6f;
		br.fill_color[1] = 0.6f;
		br.fill_color[2] = 0.0f;
		break;
	case cellType::Path:
		br.fill_color[0] = 1.f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.2f;
		break;
	}

	br.outline_opacity = 1.0f;
	graphics::drawRect(x, y, size,size, br);

	
}

bool Node::contains(float px, float py) const {
	return px >= x - size / 2 &&
		px <= x + size / 2 &&
		py >= y - size / 2 &&
		py <= y + size / 2;
}