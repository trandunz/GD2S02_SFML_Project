// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : EndGameMenu.h 
// Description : EndGameMenu Header File
// Author : Inman, Will

#pragma once
class EndGameMenu
{
public:
	/// <summary>
	/// EndGameMenu Constructor
	/// </summary>
	EndGameMenu();
	/// <summary>
	/// EndGameMenu Destructor
	/// </summary>
	~EndGameMenu();

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
};

