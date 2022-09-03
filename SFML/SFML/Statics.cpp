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
