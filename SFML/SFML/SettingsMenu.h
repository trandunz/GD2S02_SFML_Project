#pragma once

class SettingsMenu
{
public:
	SettingsMenu();
	~SettingsMenu();

	bool bDestroy{ false };

private:
	void CreateMenuBackground();
	void CreateMenuButtons();
	void CreateMenuText();

	void CleanupElements();

	void CreatePlayerOneKeybinds();
	void CreatePlayerTwoKeybinds();
};

