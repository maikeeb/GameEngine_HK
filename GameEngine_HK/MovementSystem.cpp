#include "Include/MovementSystem.h"
#define X_SPEED 0.1
#define Y_SPEED 0.1

MovementSystem::MovementSystem()
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::tick(ECS::World* world, float deltaTime)
{
	if (States::GetPausedState() == false)
	{
		world->each<Transform, InputController>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<InputController> input) -> void
			{
				if (input->bIsControllerActive == true)
				{
					if (input->wKey == true)
					{
						transform->ySpeed = -Y_SPEED;
						//transform->Move();
					}
					else if (input->sKey == true)
					{
						transform->ySpeed = Y_SPEED;
						//transform->Move();
					}
					else {
						transform->ySpeed = 0;
					}

					if (input->aKey == true)
					{
						transform->xSpeed = -X_SPEED;
						//transform->Move();
					}
					else if (input->dKey == true)
					{
						transform->xSpeed = X_SPEED;
						//transform->Move();
					}
					else {
						transform->xSpeed = 0;
					}

				}
				
			}
		);
	}
}
