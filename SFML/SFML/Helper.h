// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Helper.h 
// Description : Helper Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

template<typename K, typename V>
inline void CleanupMap(std::map<K, V>& _map)
{
	auto it = _map.begin();
	while (it != _map.end())
	{
		it = _map.erase(it);
	}
	_map.clear();
}

template<typename K, typename V>
inline void CleanupMap(std::map<K, V*>& _map)
{
	for (auto& item : _map)
	{
		if (item.second != nullptr)
		{
			delete item.second;
			item.second = nullptr;
		}
	}
	_map.clear();
}

template<typename T>
inline void CleanupVector(std::vector<T*>& _vector)
{
	for (auto& item : _vector)
	{
		if (item != nullptr)
		{
			delete item;
			item = nullptr;
		}
	}
	_vector.clear();
	_vector.resize(0);
}

template<typename T>
inline void CleanupVector(std::vector<T>& _vector)
{
	_vector.clear();
	_vector.resize(0);
}

inline std::string FloatToString(float _float, int _precision = 2)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(_precision) << _float;
	return stream.str();
}

inline void Print(std::string _message, bool _newLine = true)
{
	std::cout << _message;
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(size_t _size, bool _newLine = true)
{
	std::cout << _size;
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(int _int, bool _newLine = true)
{
	std::cout << _int;
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(float _float, bool _newLine = true, int _precision = 2)
{
	std::cout << FloatToString(_float, _precision);
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(char _character, bool _newLine = true)
{
	std::cout << _character;
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(sf::Vector3f _vector3, bool _newLine = true)
{
	std::cout << "X:" << FloatToString(_vector3.x) << "|Y:" << FloatToString(_vector3.y) << "|Z:" << FloatToString(_vector3.z);
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(sf::Vector3i _vector3, bool _newLine = true)
{
	std::cout << "X:" << _vector3.x << "|Y:" << _vector3.y << "|Z:" << _vector3.z;
	if (_newLine)
		std::cout << std::endl;
}
inline void Print(sf::Vector2i _vector2, bool _newLine = true)
{
	std::cout << "X:" << _vector2.x << "|Y:" << _vector2.y;
	if (_newLine)
		std::cout << std::endl;
}

