#include "GUI.h"
#include "Math.h"

void GUI::CleanupElements()
{
	m_Texts.clear();
	m_Images.clear();
}

void GUI::CreateButton(ButtonProperties _properties)
{
}

void GUI::CreateText(std::string _key, TextProperties _properties)
{
	m_Texts.insert_or_assign(_key, sf::Text());
	m_Texts[_key].setFont(Statics::TimesNewRoman);
	m_Texts[_key].setCharacterSize(_properties.CharacterSize);
	m_Texts[_key].setFillColor(_properties.Color);
	m_Texts[_key].setString(_properties.String);
	SetOriginCenter(m_Texts[_key]);
	m_Texts[_key].setPosition(_properties.StartPos);
}

sf::Text& GUI::GetText(std::string _key)
{
	return m_Texts[_key];
}

void GUI::SetText(std::string _key, std::string _value)
{
	m_Texts[_key].setString(_value);
	SetOriginCenter(m_Texts[_key]);
}

void GUI::AppendText(std::string _key, std::string _value)
{
	m_Texts[_key].setString(m_Texts[_key].getString() + _value);
	SetOriginCenter(m_Texts[_key]);
}

void GUI::CreateImage(std::string _key, ImageProperties _properties)
{
	m_Images.insert_or_assign(_key, sf::Sprite());
	m_Images[_key].setTexture(*_properties.Texture, true);
	m_Images[_key].setScale(_properties.Scale);
	SetOriginCenter(m_Images[_key]);
	m_Images[_key].setPosition(_properties.StartPos);
}

sf::Sprite& GUI::GetImage(std::string _key)
{
	return m_Images[_key];
}

void GUI::SetImageSprite(std::string _key, sf::Texture& _texture)
{
	m_Images[_key].setTexture(_texture, true);
	SetOriginCenter(m_Images[_key]);
}

void GUI::HandleEvents()
{
	if (Statics::EventHandle.type == sf::Event::MouseButtonReleased
		&& Statics::EventHandle.mouseButton.button == sf::Mouse::Left)
	{
		//for (auto& button : m_Buttons)
		//{
		//	button->CheckForPress();
		//}
	}
}

void GUI::Update()
{

}

void GUI::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
{
	for (auto& image : m_Images)
	{
		_target.draw(image.second);
	}
	for (auto& text : m_Texts)
	{
		_target.draw(text.second);
	}
}
