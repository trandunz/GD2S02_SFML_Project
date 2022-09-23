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
	/// <summary>
	/// Pre-Loads a list of textures for use later
	/// </summary>
	/// <param name="_texturesToPreload"></param>
	static void InitTextures(std::vector<std::string> _texturesToPreload);

	/// <summary>
	/// Loads and returns a specified texture
	/// </summary>
	/// <param name="_fileName"></param>
	/// <returns></returns>
	static sf::Texture& LoadTexture(std::string _fileName);

	/// <summary>
	/// Cleans up all loaded textures
	/// </summary>
	static void CleanupTextures();

private:
	inline static std::map<std::string, sf::Texture*> m_LoadedTextures{};

public:
	///////////////////////////
	/// Getters and Setters	///
	/////////////////////////// 
};

