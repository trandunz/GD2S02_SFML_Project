#pragma once

class SettingsMenu;
class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void Update();

	bool bDestroy{ false };

private:
	void CreateMenuBackground();
	void CreateMenuButtons();
	void CreateMenuText();

	void CleanupElements();

	SettingsMenu* m_SettingsMenu{ nullptr };
};

