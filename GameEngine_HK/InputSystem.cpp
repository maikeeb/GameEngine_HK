#include "Include/InputSystem.h"

InputSystem::InputSystem(sf::RenderWindow* win) : window(win)
{
	
}

InputSystem::~InputSystem()
{
}

void InputSystem::tick(ECS::World* world, float deltaTime)
{
	GetKeyEvents(world);
}

void InputSystem::GetKeyEvents(ECS::World* world)
{
	world->each<InputController>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<InputController> input) -> void
		
	{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				input->wKey = true;
			else
			{
				input->wKey = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				input->aKey = true;
			else
			{
				input->aKey = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				input->sKey = true;
			else
			{
				input->sKey = false;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				input->dKey = true;
			else
			{
				input->dKey = false;
			}
	});
}
