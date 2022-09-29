#pragma once
#include "Statics.h"

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	bool bDestroy{ false };

private:
	void CreateMenuBackground();
	void CreateMenuButtons();
	void CreateMenuText();
};

