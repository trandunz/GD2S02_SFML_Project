#include "Statics.h"
#include "LevelLoader.h"
#include "TextureLoader.h"

void Start();
void Update();
void PollEvents();
void Render();

int Cleanup();

int main()
{
	Start();
	Update();

	return Cleanup();
}

void Start()
{
	Statics::InitRenderWindow({ 800, 800 }, "Game Name", sf::Style::Default, sf::ContextSettings());
	Statics::RenderWindow.setKeyRepeatEnabled(false);
	Statics::InitGlobalFont("TimesNewRoman.ttf");
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
			if (Statics::EventHandle.key.code == sf::Keyboard::Escape)
			{
				Statics::RenderWindow.close();
			}
			if (Statics::EventHandle.key.code == sf::Keyboard::End)
			{
				Statics::bDebugMode = !Statics::bDebugMode;
				if (Statics::bDebugMode)
					printf("Debug mode turned on");
				else
					printf("Debug mode turned off");
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
