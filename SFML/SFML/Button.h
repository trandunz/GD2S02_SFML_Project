#pragma once

#include "Statics.h"
#include "Math.h"

class Button : public sf::Drawable
{
public:
	Button();
	Button(ButtonProperties _properties);
	~Button();

	void CallOnMouseOver();
	void CallOnPress();
	void SetLabel(std::string _newLabel);
	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);
	void ResetScale();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;
	
	void SetTexture(std::string _fileName);
	void SetTexture(sf::Texture& _texture);

	ButtonProperties m_Properties;
	sf::Sprite m_Sprite;
	sf::Text m_Label;
};

