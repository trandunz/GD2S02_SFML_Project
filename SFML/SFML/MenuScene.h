// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : MenuScene.h
// Description : MenuScene Header File
// Author : Bartlett, Benjamin

#pragma once
#include "Level.h"
#include "Statics.h"

class Button;

class MenuScene : public Level
{
public:
	MenuScene();
	virtual ~MenuScene();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Draw() override;

	void ScaleSelectedButton(std::string _button);
private:
	std::string m_sHighLighted{};
	int m_iButtonSelected{};

	std::vector<std::string> m_vecButtons;

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

