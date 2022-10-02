// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Math.h 
// Description : Math Header File
// Author : Inman, Will

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
	sf::FloatRect textRect = _text.getLocalBounds();
	_text.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);
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
