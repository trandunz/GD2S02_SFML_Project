// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : TextureLoader.h 
// Description : TextureLoader Header File
// Author : Inman, Will

#pragma once
#include "Statics.h"

#define IMG_HEIGHT 32;

class TextureLoader
{
public:
	static void InitTextures(std::vector<std::string> _texturesToPreload);
	static sf::Texture& LoadTexture(std::string _fileName);
	static void CleanupTextures();

private:
	inline static std::map<std::string, sf::Texture*> m_LoadedTextures{};
};

