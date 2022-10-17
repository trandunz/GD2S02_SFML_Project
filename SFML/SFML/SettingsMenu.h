// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : SettingsMenu.h 
// Description : SettingsMenu Header File
// Author : Inman, Will

#pragma once

class SettingsMenu
{
public:
	/// <summary>
	/// SettingsMenu Constructor
	/// </summary>
	SettingsMenu();
	/// <summary>
	/// SettingsMenu Destructor
	/// </summary>
	~SettingsMenu();

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

	/// <summary>
	/// create the GUI displaying player ones keybinds
	/// </summary>
	void CreatePlayerOneKeybinds();
	/// <summary>
	/// create the GUI displaying player twos keybinds
	/// </summary>
	void CreatePlayerTwoKeybinds();
};

