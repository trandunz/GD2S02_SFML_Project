#pragma once
#include "Helper.h"

#define PI 3.141592654f

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

inline float ToDegrees(float _inAngleRad)
{
	return (_inAngleRad * (180.0f / PI));
}

inline float ToRad(float _inAngleDegrees)
{
	return (_inAngleDegrees * (PI / 180.0f));
}
