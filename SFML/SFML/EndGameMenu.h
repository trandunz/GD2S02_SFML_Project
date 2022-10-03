#pragma once
class EndGameMenu
{
public:
	EndGameMenu();
	~EndGameMenu();

private:
	void CreateMenuBackground();
	void CreateMenuButtons();
	void CreateMenuText();

	void CleanupElements();
};

