#pragma once


#include "ECS.h"
#include <SFML/Graphics.hpp>
#include "Components.h"
#include "../States.h"


class InputSystem
	:public ECS::EntitySystem
{
private:
	sf::RenderWindow* window;
public:
	InputSystem(sf::RenderWindow* win);
	~InputSystem();

	virtual void tick(ECS::World* world, float deltaTime) override;

	void GetKeyEvents(ECS::World* world); 
};

