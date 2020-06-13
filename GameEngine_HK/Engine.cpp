#include "Engine.h"

Engine::Engine(){}

Engine::~Engine(){}

void Engine::Update()
{
	sf::Event event;
	while (window -> pollEvent(event))
	{
		//"close requested" event: we close the window
		if (event.type == sf::Event::Closed)
		{
			window -> close();
		}
	}
}

Engine& Engine::GetInstance()
{
	static Engine _instance;

	return _instance;
}

void Engine::Start(sf::RenderWindow* win)
{
	bIsQuit = false;
	window = win;

	// run the program as long as the window is open
	while (window -> isOpen())
	{
		Update();
	}
}
