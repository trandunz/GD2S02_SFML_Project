#pragma once
#include "Statics.h"
#include <sstream>
#include <iomanip>

inline float Magnitude(sf::Vector2f _vec)
{
	return sqrtf((_vec.x * _vec.x) + (_vec.y * _vec.y));
}

inline void SetOriginCenter(sf::Sprite& _sprite)
{
	_sprite.setOrigin(_sprite.getLocalBounds().width / 2.0f, _sprite.getLocalBounds().height / 2.0f);
}

inline void SetOriginCenter(sf::Text& _text)
{
	_text.setOrigin(_text.getGlobalBounds().width / 2, _text.getGlobalBounds().height / 2);
}

inline sf::Vector2f Normalize(sf::Vector2f _vec)
{
	return _vec / Magnitude(_vec);
}

inline std::string FloatToString(float _float, int _precision = 2)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(_precision) << _float;
	return stream.str();
}

