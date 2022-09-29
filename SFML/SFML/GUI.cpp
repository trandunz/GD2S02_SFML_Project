// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : GUI.cpp 
// Description : GUI Implementation File		
// Author : Inman, Will

#include "GUI.h"
#include "Math.h"
#include "Button.h"
#include "Helper.h"

GUI& GUI::GetInstance()
{
	static GUI instance;
	return instance;
}

void GUI::CleanupElements()
{
	CleanupMap(m_vecTexts);
	CleanupMap(m_vecImages);
	CleanupMap(m_vecButtons);
}

void GUI::CleanupImageElement(std::string _key)
{
	if (m_vecImages.contains(_key))
	{
		m_vecImages.erase(m_vecImages.find(_key));
	}
}

void GUI::CleanupTextElement(std::string _key)
{
	if (m_vecTexts.contains(_key))
	{
		m_vecTexts.erase(m_vecTexts.find(_key));
	}
}

void GUI::CleanupButtonElement(std::string _key)
{
	if (m_vecButtons.contains(_key))
	{
		m_vecButtons.erase(m_vecButtons.find(_key));
	}
}

void GUI::CreateButton(std::string _key, ButtonProperties _properties)
{
	m_vecButtons.insert_or_assign(_key, Button(_properties));
}

Button* GUI::GetButton(std::string _key)
{
	if (m_vecButtons.contains(_key))
		return &m_vecButtons[_key];
	else
		return nullptr;
}

void GUI::ResetAllButtonsScale()
{
	for (auto& button : m_vecButtons)
	{
		button.second.ResetScale();
	}
}

void GUI::CreateText(std::string _key, TextProperties _properties)
{
	m_vecTexts.insert_or_assign(_key, sf::Text());
	m_vecTexts[_key].setFont(Statics::TimesNewRoman);
	m_vecTexts[_key].setCharacterSize(_properties.iCharacterSize);
	m_vecTexts[_key].setFillColor(_properties.Color);
	m_vecTexts[_key].setString(_properties.String);
	SetOriginCenter(m_vecTexts[_key]);
	m_vecTexts[_key].setPosition(_properties.v2fStartPos);
}

sf::Text& GUI::GetText(std::string _key)
{
	return m_vecTexts[_key];
}

void GUI::SetText(std::string _key, std::string _value)
{
	m_vecTexts[_key].setString(_value);
	SetOriginCenter(m_vecTexts[_key]);
}

void GUI::AppendText(std::string _key, std::string _value)
{
	m_vecTexts[_key].setString(m_vecTexts[_key].getString() + _value);
	SetOriginCenter(m_vecTexts[_key]);
}

void GUI::CreateImage(std::string _key, ImageProperties _properties)
{
	m_vecImages.insert_or_assign(_key, sf::Sprite());
	m_vecImages[_key].setTexture(*_properties.Texture, true);
	m_vecImages[_key].setScale(_properties.v2fScale);
	SetOriginCenter(m_vecImages[_key]);
	m_vecImages[_key].setPosition(_properties.v2fStartPos);
}

sf::Sprite& GUI::GetImage(std::string _key)
{
	return m_vecImages[_key];
}

void GUI::SetImageSprite(std::string _key, sf::Texture& _texture)
{
	m_vecImages[_key].setTexture(_texture, true);
	SetOriginCenter(m_vecImages[_key]);
}

void GUI::HandleEvents()
{
	if (Statics::EventHandle.type == sf::Event::MouseButtonReleased
		&& Statics::EventHandle.mouseButton.button == sf::Mouse::Left)
	{
		for (auto& button : m_vecButtons)
		{
			button.second.CallOnMouseOver();
		}
	}
}

void GUI::Update()
{

}

void GUI::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& image : m_vecImages)
	{
		_target.draw(image.second);
	}
	for (auto& text : m_vecTexts)
	{
		_target.draw(text.second);
	}
	for (auto& button : m_vecButtons)
	{
		_target.draw(button.second);
	}
}
