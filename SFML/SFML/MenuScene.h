#pragma once
#include <vector>
#include "Statics.h"
#include "Level.h"

class Button;

class MenuScene : public Level
{
public:
	MenuScene();
	virtual ~MenuScene();

	virtual void HandleEvents() override;
	virtual void Update() override;
	virtual void Draw() override;

	void ScaleSelectedButton(std::string _button);
private:
	std::string m_sHighLighted;
	int m_iButtonSelected;
};

