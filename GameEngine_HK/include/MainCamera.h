#pragma once

#include <SFML/Graphics.hpp>
#include "ECS.h"


class MainCamera
{
public:
	sf::View cameraView;

	MainCamera();
	MainCamera(sf::Vector2f pivot);
	~MainCamera();

	void Update(ECS::World* world, float deltaTime, sf::RenderWindow* gameWindow);
};

