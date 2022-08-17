#pragma once

class Level
{
public:
	Level() {}
	virtual ~Level() {}

	virtual void HandleEvents() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
};