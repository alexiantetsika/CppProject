#pragma once
#include "grid.h"
class Game {
private:
	Game();
public:
	static Game& getInstance();
	Grid* grid;

	void init();
	void update(float dt);
	void draw();
	void runAStar();
	
	~Game();
};

