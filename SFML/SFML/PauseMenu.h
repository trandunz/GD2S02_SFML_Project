// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : PauseMenu.h 
// Description : PauseMenu Header File
// Author : Inman, Will

#pragma once

#include "Statics.h"
class SettingsMenu;
class PauseMenu
{
public:
	/// <summary>
	/// Pause Menu Constructor
	/// </summary>
	PauseMenu();
	/// <summary>
	/// Pause Menu Destructor
	/// </summary>
	~PauseMenu();

	/// <summary>
	/// Pause menu update
	/// </summary>
	void Update();

	/// <summary>
	/// Handles which button is selected
	/// and if enter is pressed calls the
	/// selected buttons CallOnPress() function
	/// </summary>
	void HandleEvents();

	/// <summary>
	/// Scales the selected button up and down.
	/// </summary>
	/// <param name="_button"></param>
	void ScaleSelectedButton(std::string _button);

	bool bDestroy{ false };

private:
	/// <summary>
	/// Creates the background for the menu
	/// </summary>
	void CreateMenuBackground();
	/// <summary>
	/// Creates the Buttons for the menu
	/// </summary>
	void CreateMenuButtons();
	/// <summary>
	/// Creates the text for the menu
	/// </summary>
	void CreateMenuText();

	/// <summary>
	/// Cleans up all the GUI elements in the menu
	/// </summary>
	void CleanupElements();

	SettingsMenu* m_SettingsMenu{ nullptr };
	std::vector<std::string> m_vecButtons;
	int m_iButtonSelected{};
	bool m_bPlayMenuMove{};
	bool m_bButtonReleased{};

};

