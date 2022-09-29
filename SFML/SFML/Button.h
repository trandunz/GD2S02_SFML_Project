// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Button.h 
// Description : Button Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

class Button : public sf::Drawable
{
public:
	Button();
	Button(ButtonProperties _properties);
	~Button();

	bool CallOnMouseOver();
	void CallOnPress();
	sf::Sprite GetSprite()const;

	void ResetScale();
private:
	virtual void draw(sf::RenderTarget& _target, sf::RenderStates _states) const;

	ButtonProperties m_Properties{};
	sf::Sprite m_Sprite{};
	sf::Text m_Label{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 

	void SetLabel(std::string _newLabel);
	void SetPosition(sf::Vector2f _position);
	void SetScale(sf::Vector2f _scale);

	void SetTexture(std::string _fileName);
	void SetTexture(sf::Texture& _texture);
};

