#include "Include/Engine.h"

Engine::Engine(){}

Engine::~Engine(){}

void Engine::Update()
{
	// use _ at the beginning of a local variable
	sf::Event _event;
	while (window -> pollEvent(_event))
	{
	
		//"close requested" event: we close the window
		if (_event.type == sf::Event::Closed)
		{
			std::cout << "Closing now..." << std::endl;
			window -> close();
		}

		pauseMenu.Update(_event, 10.0f, this->window);

	}
	
	world->tick(10.0f); // milliseconds inbetween ticks

	mainCam.Update(world, 10.0f, window);

	if (States::GetPausedState() == true)
	{
		GameInactiveStaticActions();
	}
}

void Engine::GameInactiveStaticActions()
{
	pauseMenu.Render(this->window, 10.0f, mainCam.cameraView.getCenter());
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

	pauseMenu = PauseMenu(this->window);
	mainCam = MainCamera(sf::Vector2f(
		this->window->getSize().x / 2, 
		this->window->getSize().y / 2));

	// run the program as long as the window is open
	while (window -> isOpen())
	{
		Update();
	}

	
}

void Engine::AddSystem(ECS::EntitySystem* newSys)
{
	world->registerSystem(newSys);
	world->enableSystem(newSys);
}
