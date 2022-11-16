// Bachelor of Software Engineering 
// Media Design School 
// Auckland 
// New Zealand 
// (c) Media Design School
// File Name : Main.cpp 
// Description : Main Implementation File		
// Author :

#include "LevelLoader.h"
#include "TextureLoader.h"

/// <summary>
/// Main Init / Start Function
/// </summary>
void Start();
/// <summary>
/// Main Update function
/// </summary>
void Update();
/// <summary>
/// Main Poll Events Function
/// </summary>
void PollEvents();
/// <summary>
/// Main Render Function
/// </summary>
void Render();

/// <summary>
/// End of program cleanup function
/// </summary>
/// <returns></returns>
int Cleanup();

int main()
{
	Start();
	Update();

	return Cleanup();
}

void Start()
{
	Statics::InitRenderWindow({ 800, 800 }, "Abracadabros");
	Statics::RenderWindow.setKeyRepeatEnabled(false);
	Statics::InitGlobalFont("MetalMania.ttf");
	LevelLoader::LoadLevel(LEVELS::MENUSCENE);
}

void Update()
{
	while (Statics::RenderWindow.isOpen())
	{
		Statics::CalculateDeltaTime();
		PollEvents();

		LevelLoader::Update();

		Render();

		LevelLoader::SwitchToLoadedLevel();
	}
}

void PollEvents()
{
	if (Statics::RenderWindow.pollEvent(Statics::EventHandle))
	{
		if (Statics::EventHandle.type == sf::Event::KeyPressed)
		{
			if (Statics::EventHandle.key.code == sf::Keyboard::Key::End)
			{
				Statics::ToggleDebug();
			}
		}
		if (Statics::EventHandle.type == sf::Event::Closed)
		{
			Statics::RenderWindow.close();
		}

		LevelLoader::HandleEvents();
	}
}

void Render()
{
	Statics::RenderWindow.clear();

	LevelLoader::Draw();

	Statics::RenderWindow.display();
}

int Cleanup()
{
	TextureLoader::CleanupTextures();
	LevelLoader::CleanupLevel();

	return 0;
}
