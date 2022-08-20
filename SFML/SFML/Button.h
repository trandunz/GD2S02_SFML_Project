#pragma once

#include "Statics.h"
#include "Math.h"

typedef void (*callback_function)(void);

struct ButtonProperties
{
	std::string Label{};
	sf::Vector2f Position{};
	callback_function OnPressLambda = nullptr;
	sf::Vector2f Scale = { 1,1 };
};

class Button : public sf::Drawable
{
public:
	Button(ButtonProperties _properties);
	~Button();

	void CallOnPress();
	void SetLabel(std::string _newLabel);
	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	void SetTexture(std::string _fileName);

	ButtonProperties m_Properties;
	sf::Sprite m_Sprite;
	sf::Text m_Label;
};

