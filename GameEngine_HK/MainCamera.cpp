#include "include\MainCamera.h"

MainCamera::MainCamera()
{
}

MainCamera::MainCamera(sf::Vector2f pivot)
{
	cameraView.setCenter(pivot);
}

MainCamera::~MainCamera()
{
}

void MainCamera::Update(ECS::World* world, float deltaTime, sf::RenderWindow* gameWindow)
{
	sf::Vector2f _windowSize(gameWindow->getSize().x, gameWindow->getSize().y);
	cameraView.setSize(_windowSize);

	float _cameraMoveSpeed = 0.01f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		cameraView.move(-_cameraMoveSpeed * deltaTime, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		cameraView.move(_cameraMoveSpeed * deltaTime, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		cameraView.move(0,-_cameraMoveSpeed * deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		cameraView.move(0, _cameraMoveSpeed * deltaTime);
	}

	gameWindow->setView(cameraView);
}
