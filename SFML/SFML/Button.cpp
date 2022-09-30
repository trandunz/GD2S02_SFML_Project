// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Button.cpp 
// Description : Button Implementation File		
// Author : Inman, Will

#include "Button.h"
#include "TextureLoader.h"
#include "Math.h"

Button::Button()
{
}

Button::Button(ButtonProperties _properties)
{
	m_Label.setFont(Statics::TimesNewRoman);
	m_Label.setString(_properties.Label);
	m_Label.setCharacterSize(24); 
	m_Label.setFillColor(sf::Color::Black);
	m_Properties = _properties;
	if (_properties.Texture == nullptr)
	{
		SetTexture("Button.png");
	}
	else
	{
		SetTexture(*_properties.Texture);
	}
	SetScale(_properties.v2fScale);
	SetPosition(_properties.v2fStartPos);
}

Button::~Button()
{
	m_Properties.OnPressFunction = nullptr;
}

bool Button::CallOnMouseOver()
{
	bool wasPressed = false;
	if (m_Properties.OnPressFunction != nullptr)
	{
		sf::Vector2f mousePos = { (float)sf::Mouse::getPosition(Statics::RenderWindow).x, (float)sf::Mouse::getPosition(Statics::RenderWindow).y };
		if (m_Sprite.getGlobalBounds().contains(mousePos))
		{
			wasPressed = true;
			m_Properties.OnPressFunction();
		}
	}

	return wasPressed;
}

void Button::CallOnPress()
{
	if (m_Properties.OnPressFunction != nullptr)
	{
		m_Properties.OnPressFunction();
	}
}

sf::Sprite Button::GetSprite() const
{
	return m_Sprite;
}

void Button::SetLabel(std::string _newLabel)
{
	m_Label.setString(_newLabel);
}

void Button::SetPosition(sf::Vector2f _position)
{
	m_Sprite.setPosition(_position);
	m_Label.setPosition(_position);
}

void Button::SetScale(sf::Vector2f _scale)
{
	m_Sprite.setScale(_scale);
	m_Label.setCharacterSize(m_Label.getCharacterSize() * (unsigned)Magnitude(_scale));
	SetOriginCenter(m_Label);
}

void Button::ResetScale()
{
	SetScale(m_Properties.v2fScale);
}

void Button::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	_target.draw(m_Sprite);
	_target.draw(m_Label);

}

void Button::SetTexture(std::string _fileName)
{
	m_Sprite.setTexture(TextureLoader::LoadTexture(_fileName), true);
	SetOriginCenter(m_Sprite);
}

void Button::SetTexture(sf::Texture& _texture)
{
	m_Sprite.setTexture(_texture, true);
	SetOriginCenter(m_Sprite);
}
