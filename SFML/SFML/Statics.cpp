#include "Statics.h"

sf::RenderWindow Statics::RenderWindow{};
sf::Event Statics::EventHandle{};
sf::Font Statics::TimesNewRoman{};
sf::Clock Statics::Time{};
float Statics::TimeScale{ 1.0f };
float Statics::DeltaTime{};
float Statics::UnscaledDeltaTime{};
float Statics::LastTime{};
float Statics::m_fGameScore{};

void Statics::CalculateDeltaTime()
{
	float currentTime = Time.getElapsedTime().asSeconds();
	UnscaledDeltaTime = currentTime - LastTime;
	DeltaTime = UnscaledDeltaTime * TimeScale;
	LastTime = currentTime;
}
