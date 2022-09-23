// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : CharacterSelectScene.h 
// Description : CharacterSelectScene Header File
// Author : 

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

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

