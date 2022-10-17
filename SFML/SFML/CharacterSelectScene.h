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
	/// <summary>
	/// CharacterSelectScene Constructor
	/// </summary>
	CharacterSelectScene();
	/// <summary>
	/// CharacterSelectScene Destructor
	/// </summary>
	virtual ~CharacterSelectScene();

	/// <summary>
	/// Handles all key and mouse events
	/// </summary>
	virtual void HandleEvents() override;
	/// <summary>
	/// Update everything in the scene
	/// </summary>
	virtual void Update() override;
	/// <summary>
	/// Draw everything in the scene
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// Scale the selected button too look selected
	/// </summary>
	/// <param name="_button"></param>
	void ScaleSelectedButton(std::string _button);
	/// <summary>
	/// Scale the specified image too look selected
	/// </summary>
	/// <param name="_image"></param>
	void ScaleImage(std::string _image);

	/// <summary>
	/// Select the player on the left
	/// </summary>
	/// <param name="_player"></param>
	/// <returns></returns>
	int SelectLeft(int _player);
	/// <summary>
	/// Select the player on the right
	/// </summary>
	/// <param name="_player"></param>
	/// <returns></returns>
	int SelectRight(int _player);

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

	void SetPlayerPosition(std::string _player, int _playerPosition);
	ELEMENTTYPE SetPlayerElement(int _player);
};

