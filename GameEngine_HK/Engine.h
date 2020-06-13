#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>

class Engine
{
private:
	bool bIsQuit;

	Engine();

	// singleton: required to prevent the reference from being copied, or assigned
	Engine(Engine& copy);		// hide copy constructor
	Engine(Engine&& other);		// hide move contructor
	Engine& operator= (Engine& copy); //hide assignment operator
	~Engine();
	void Update();

public:
	sf::RenderWindow* window;

	static Engine& GetInstance();
	void Start(sf::RenderWindow* win);
};

