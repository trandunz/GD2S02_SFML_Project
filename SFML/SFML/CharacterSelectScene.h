#pragma once
#include "Level.h"
#include "Statics.h"

class Button;

class CharacterSelectScene : public Level
{
public:
	CharacterSelectScene();
	virtual ~CharacterSelectScene();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Draw() override;
private:

};

