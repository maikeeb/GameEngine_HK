#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include "ECS.h"

#include "RenderingSystem.h"
#include "AnimationSystem.h"
#include "InputSystem.h"
#include "MovementSystem.h"
#include "PhysicsSystem.h"
#include "TileMapSystem.h"

#include "MainCamera.h"	
#include "PauseMenu.h"
#include "Components.h"


class Engine
{
private:
	bool bIsQuit;

	Engine();

	// singleton: required to prevent the reference from being copied, or assigned
	Engine(Engine& copy);		// hide copy constructor
	Engine(Engine&& other);		// hide move constructor
	Engine& operator= (Engine& copy); //hide assignment operator

	~Engine();
	void Update();
	void GameInactiveStaticActions();

public:
	sf::RenderWindow* window;
	ECS::World* world;
	MainCamera mainCam;
	PauseMenu pauseMenu;

	static Engine& GetInstance();
	void Start(sf::RenderWindow* win);
	void AddSystem(ECS::EntitySystem* newSys);
};

