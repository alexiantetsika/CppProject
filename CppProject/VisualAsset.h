#pragma once

class visualAsset {
public:
	virtual void draw() = 0;
	virtual void update(float dt) {}
	virtual ~visualAsset() = default;
};