#pragma once
#include "Level.h"

class MenuScene : public Level
{
public:
	MenuScene();
	virtual ~MenuScene();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Draw() override;
private:


};

