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

class SettingsMenu;
class MenuScene : public Level
{
public:
	/// <summary>
	/// Constructor for the Menu Scene
	/// Creates all the buttons with GUI
	/// and adds them to the m_vecButtons vector
	/// </summary>
	MenuScene();

	/// <summary>
	/// Destructor for Menu Scene
	/// Calls clean up for the GUI elements
	/// </summary>
	virtual ~MenuScene();

	/// <summary>
	/// Handles which button is selected
	/// and if enter is pressed calls the
	/// selected buttons CallOnPress() function
	/// </summary>
	virtual void HandleEvents() override;

	/// <summary>
	/// Calls GUI::GetInstance().Update(),
	/// GUI::GetInstance().ResetAllButtonsScale(),
	/// and ScaleSelectedButton()
	/// </summary>
	virtual void Update() override;

	/// <summary>
	/// Calls the render function for GUI
	/// </summary>
	virtual void Draw() override;

	/// <summary>
	/// Scales the selected button up and down.
	/// </summary>
	/// <param name="_button"></param>
	void ScaleSelectedButton(std::string _button);
private:
	void CleanupElements();
	void CreateElements();

	std::string m_sHighLighted{};
	int m_iButtonSelected{};
	SettingsMenu* m_SettingsMenu{ nullptr };

	std::vector<std::string> m_vecButtons;

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

