#include "Statics.h"
#include "LevelLoader.h"


void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings);
void InitGlobalFont(std::string _fileName);

void Start();
void Update();
void PollEvents();
void Render();

int Cleanup();

int main()
{
	Start();
	Update();
	Render();

	return Cleanup();
}

void InitRenderWindow(sf::Vector2i _size, std::string _title, sf::Uint32 _style, sf::ContextSettings _settings)
{
	Statics::RenderWindow.create(sf::VideoMode(_size.x, _size.y), _title, _style, _settings);
}

void InitGlobalFont(std::string _fileName)
{
	Statics::TimesNewRoman.loadFromFile("Resources/Fonts/" + _fileName);
}

void Start()
{
	InitRenderWindow({ 800, 800 }, "Game Name", sf::Style::Default, sf::ContextSettings());
	Statics::RenderWindow.setKeyRepeatEnabled(false);
	InitGlobalFont("TimesNewRoman.ttf");
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
