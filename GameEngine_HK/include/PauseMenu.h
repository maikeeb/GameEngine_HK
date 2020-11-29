#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h"
#include "ButtonMap.h"
#include "../States.h"


class PauseMenu
{
public:
	PauseMenu();
	PauseMenu(sf::RenderWindow* window);
	~PauseMenu();

	void Update(sf::Event event, float deltaTime, sf::RenderWindow* window);
	void Render(sf::RenderWindow* window, float deltaTime, sf::Vector2f resumePosition);

private:
	void InitButtons();
	void Quit(sf::RenderWindow* window);

};

