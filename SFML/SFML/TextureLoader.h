#pragma once
#include "SFML/Graphics/Texture.hpp"
#include <map>

#define IMG_HEIGHT 32;

class TextureLoader
{
public:
	static void InitTextures(std::vector<std::string> _texturesToPreload);
	static sf::Texture& LoadTexture(std::string _fileName);
	static void CleanupTextures();

private:
	inline static std::map<std::string, sf::Texture*> m_LoadedTextures;
};

