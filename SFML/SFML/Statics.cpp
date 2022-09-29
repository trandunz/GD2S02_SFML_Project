// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Statics.cpp 
// Description : Statics Implementation File		
// Author : Inman, Will

#include "Statics.h"

sf::RenderWindow Statics::RenderWindow{};
sf::Event Statics::EventHandle{};
sf::Font Statics::TimesNewRoman{};
sf::Clock Statics::Time{};
float Statics::fTimeScale{ 1.0f };
float Statics::fDeltaTime{};
float Statics::fUnscaledDeltaTime{};
float Statics::m_fLastTime{};
float Statics::fGameScore{};
bool Statics::bDebugMode{ false };
float Statics::fBackgroundScrollSpeed{ 100 };

void Statics::CalculateDeltaTime()
{
	float currentTime = Time.getElapsedTime().asSeconds();
	fUnscaledDeltaTime = currentTime - m_fLastTime;
	fDeltaTime = fUnscaledDeltaTime * fTimeScale;
	m_fLastTime = currentTime;
}

void Statics::InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings)
{
	Statics::RenderWindow.create(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
}

void Statics::InitGlobalFont(std::string _fileName)
{
	Statics::TimesNewRoman.loadFromFile("Resources/Fonts/" + _fileName);
}

void Statics::SetPaused(bool _paused)
{
	if (_paused)
		fTimeScale = 0.0f;
	else
		fTimeScale = 1.0f;
}
