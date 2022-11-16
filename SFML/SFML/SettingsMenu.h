// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : SettingsMenu.h 
// Description : SettingsMenu Header File
// Author : Inman, Will

#pragma once
#include <string>

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

	/// <summary>
	/// Handles which button is selected
	/// and if enter is pressed calls the
	/// selected buttons CallOnPress() function
	/// </summary>
	void HandleEvents();

	std::string GetAudioTypeButton() { return m_sAudioType; };
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

	/// <summary>
	/// Increases/Decreases the volume of Music/Effects.
	/// </summary>
	/// <param name="_increaseOrDecrease"></param>
	/// <param name="_volumeToAdjust"></param>
	void AdjustVolume(std::string _increaseOrDecrease, std::string _volumeToAdjust);

	/// <summary>
	/// Handles the icon for mute/unmute when unmuting.
	/// </summary>
	void UnMuteIconChange(std::string _audioType);

	std::string m_sAudioType{};
	std::string m_sAdjustAudio{};
	bool m_bButtonReleased{};
};

