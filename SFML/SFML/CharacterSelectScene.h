// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : CharacterSelectScene.h 
// Description : CharacterSelectScene Header File
// Author : Bartlett, Benjamin

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

	void ScaleSelectedButton(std::string _button);
	void ScaleImage(std::string _image);

	int SelectLeft(int _player);
	int SelectRight(int _player);

	void SetPlayerPosition(std::string _player, int _playerPosition);
	ELEMENTTYPE SetPlayerElement(int _player);

private:
	sf::Vector2f m_v2fPosition1;
	sf::Vector2f m_v2fPosition2;
	sf::Vector2f m_v2fPosition3;

	int m_iPlayer1Selection;
	int m_iPlayer2Selection;

	bool m_bPlayer1Selected;
	bool m_bPlayer2Selected;

	std::string m_sFireElement;
	std::string m_sEarthElement;
	std::string m_sWaterElement;
public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

