#include "include/PauseMenu.h"

PauseMenu::PauseMenu()
{
}

PauseMenu::PauseMenu(sf::RenderWindow* window)
{
	States::SetPausedState(false);
	InitButtons();
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(sf::Event event, float deltaTime, sf::RenderWindow* window)
{
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			ButtonMap::GetMap()["RESUME"]->bIsHighlighted = false;
			ButtonMap::GetMap()["SAVE"]->bIsHighlighted = false;
			ButtonMap::GetMap()["QUIT"]->bIsHighlighted = false;
			ButtonMap::GetMap()["LOAD"]->bIsHighlighted = false;
			States::SetPausedState(States::GetPausedState() == false);
		}
	}

	/*if (event.type == sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		States::SetPausedState(States::GetPausedState() == false);
	}*/

	ButtonMap::GetMap()["RESUME"]->Update(event, deltaTime);
	ButtonMap::GetMap()["LOAD"]->Update(event, deltaTime);
	ButtonMap::GetMap()["SAVE"]->Update(event, deltaTime);
	ButtonMap::GetMap()["QUIT"]->Update(event, deltaTime);

	if (ButtonMap::GetMap()["RESUME"]->bIsClicked == true)
	{
		ButtonMap::GetMap()["RESUME"]->bIsHighlighted = false; // previous bug made the pause menu overide the tilemap
		States::SetPausedState(States::GetPausedState() == false);

		ButtonMap::GetMap()["RESUME"]->bIsClicked = false;
	}

	if (ButtonMap::GetMap()["QUIT"]->bIsClicked == true)
	{
		ButtonMap::GetMap()["QUIT"]->bIsHighlighted = false;
		Quit(window);
		ButtonMap::GetMap()["QUIT"]->bIsClicked = false;
	}

	
}

void PauseMenu::Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePosition)
{
	sf::Vector2f _sizeOffset = sf::Vector2f(
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().x / 2,
		ButtonMap::GetMap()["RESUME"]->buttonBG.getSize().y / 2);

	sf::Font _arial;
	_arial.loadFromFile("../Debug/Fonts/arial.ttf");

	ButtonMap::GetMap()["RESUME"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -80) - _sizeOffset);
	ButtonMap::GetMap()["RESUME"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["RESUME"]->buttonText.setPosition(ButtonMap::GetMap()["RESUME"]->buttonBG.getPosition());
	ButtonMap::GetMap()["RESUME"]->HighLight(window);
	ButtonMap::GetMap()["RESUME"]->Render(window, deltaTime);

	ButtonMap::GetMap()["LOAD"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, -40) - _sizeOffset);
	ButtonMap::GetMap()["LOAD"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["LOAD"]->buttonText.setPosition(ButtonMap::GetMap()["LOAD"]->buttonBG.getPosition());
	ButtonMap::GetMap()["LOAD"]->HighLight(window);
	ButtonMap::GetMap()["LOAD"]->Render(window, deltaTime);

	ButtonMap::GetMap()["SAVE"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 0) - _sizeOffset);
	ButtonMap::GetMap()["SAVE"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["SAVE"]->buttonText.setPosition(ButtonMap::GetMap()["SAVE"]->buttonBG.getPosition());
	ButtonMap::GetMap()["SAVE"]->HighLight(window);
	ButtonMap::GetMap()["SAVE"]->Render(window, deltaTime);

	ButtonMap::GetMap()["QUIT"]->buttonBG.setPosition(resumePosition + sf::Vector2f(0, 40) - _sizeOffset);
	ButtonMap::GetMap()["QUIT"]->buttonText.setFont(_arial);
	ButtonMap::GetMap()["QUIT"]->buttonText.setPosition(ButtonMap::GetMap()["QUIT"]->buttonBG.getPosition());
	ButtonMap::GetMap()["QUIT"]->HighLight(window);
	ButtonMap::GetMap()["QUIT"]->Render(window, deltaTime);

	window->display();
}

void PauseMenu::InitButtons()
{
	sf::Vector2f _size = sf::Vector2f(125, 30);

	ButtonMap::GetMap().insert(
		{
			"RESUME", new Button(_size, sf::Color(100,100,100, 255), "Resume Game")
		});

	ButtonMap::GetMap().insert(
		{
			"LOAD", new Button(_size, sf::Color(100,100,100, 255), "Load Tile Map")
		});

	ButtonMap::GetMap().insert(
		{
			"SAVE", new Button(_size, sf::Color(100,100,100, 255), "Save Tile Map")
		});

	ButtonMap::GetMap().insert(
		{
			"QUIT", new Button(_size, sf::Color(100,100,100, 255), "Quit Game")
		});
}

void PauseMenu::Quit(sf::RenderWindow* window)
{
	window->close();
}
