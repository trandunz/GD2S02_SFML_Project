#include "GUI.h"
#include "Math.h"
#include "Button.h"

void GUI::CleanupElements()
{
	m_vecTexts.clear();
	m_vecImages.clear();
	m_vecButtons.clear();
}

void GUI::CreateButton(std::string _key, ButtonProperties _properties)
{
	m_vecButtons.insert_or_assign(_key, Button(_properties));
}

Button& GUI::GetButton(std::string _key)
{
	return m_vecButtons[_key];
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
	m_vecTexts[_key].setCharacterSize(_properties.CharacterSize);
	m_vecTexts[_key].setFillColor(_properties.Color);
	m_vecTexts[_key].setString(_properties.String);
	SetOriginCenter(m_vecTexts[_key]);
	m_vecTexts[_key].setPosition(_properties.StartPos);
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
	m_vecImages[_key].setScale(_properties.Scale);
	SetOriginCenter(m_vecImages[_key]);
	m_vecImages[_key].setPosition(_properties.StartPos);
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
