#include "Include/PhysicsSystem.h"


bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity,
	float x, float y)
{
	// check X for collision

	if (touchingEntity->rightEdge + x > touchedEntity->leftEdge &&
		touchedEntity->rightEdge > touchingEntity->leftEdge + x)
	{
		// Check Y for collision
		if (touchingEntity->bottomEdge + y > touchedEntity->topEdge &&
			touchedEntity->bottomEdge > touchingEntity->topEdge + y)
		{
			return true;
		}
	}



	return false;
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle,
	float x, float y)
{
	float _touchedRectangleLeft = touchedRectangle.getPosition().x;
	float _touchedRectangleRight = touchedRectangle.getPosition().x + touchedRectangle.getGlobalBounds().width;
	float _touchedRectTop = touchedRectangle.getPosition().y;
	float _touchedRectBottom = touchedRectangle.getPosition().y + touchedRectangle.getGlobalBounds().height;


	// check X for collision
	if (touchingEntity->rightEdge + x > _touchedRectangleLeft &&
		_touchedRectangleRight > touchingEntity->leftEdge + x)
	{
		// Check Y for collision
		if (touchingEntity->bottomEdge + y > _touchedRectTop &&
			_touchedRectBottom > touchingEntity->topEdge + y)
		{
			return true;
		}
	}

	return false;
}

bool PhysicsSystem::IsColliding(
	ECS::ComponentHandle<BoxCollider> touchingBox,
	ECS::ComponentHandle<BoxCollider> touchedBox)
{

	if (touchingBox->rightEdge > touchedBox->leftEdge &&
		touchedBox->rightEdge > touchingBox->leftEdge)
	{
		if (touchingBox->bottomEdge > touchedBox->topEdge &&
			touchedBox->bottomEdge > touchingBox->topEdge)
		{
			return true;
		}
	}
	return false;
}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	ECS::ComponentHandle<BoxCollider> touchedEntity)
{
	// Scenario dealing with collision from the right side by accelerating rightward
	if (touchingEntity->rightEdge + transform->xSpeed > touchedEntity->leftEdge &&
		touchingEntity->topEdge  < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge &&
		transform->xSpeed > 0)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating downward
	if (touchingEntity->bottomEdge + transform->ySpeed > touchedEntity->topEdge &&
		touchingEntity->leftEdge  < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge &&
		transform->ySpeed > 0)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating leftward
	if (touchingEntity->leftEdge + transform->xSpeed < touchedEntity->rightEdge &&
		touchingEntity->topEdge  < touchedEntity->bottomEdge &&
		touchingEntity->bottomEdge > touchedEntity->topEdge &&
		transform->xSpeed < 0)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating upward
	if (touchingEntity->topEdge + transform->ySpeed < touchedEntity->bottomEdge &&
		touchingEntity->leftEdge  < touchedEntity->rightEdge &&
		touchingEntity->rightEdge > touchedEntity->leftEdge &&
		transform->ySpeed < 0)
	{
		transform->ySpeed = 0;
	}

}

void PhysicsSystem::CheckCollisionSides(
	ECS::ComponentHandle<Transform> transform,
	ECS::ComponentHandle<BoxCollider> touchingEntity,
	sf::RectangleShape touchedRectangle)
{
	float _touchedRectangleLeft = touchedRectangle.getPosition().x;
	float _touchedRectangleRight = touchedRectangle.getPosition().x + touchedRectangle.getGlobalBounds().width;
	float _touchedRectangleTop = touchedRectangle.getPosition().y;
	float _touchedRectangleBottom = touchedRectangle.getPosition().y + touchedRectangle.getGlobalBounds().height;


	// Scenario dealing with collision from the right side by accelerating rightward
	if (touchingEntity->rightEdge + transform->xSpeed > _touchedRectangleLeft &&
		touchingEntity->topEdge  < _touchedRectangleBottom &&
		touchingEntity->bottomEdge > _touchedRectangleTop &&
		transform->xSpeed > 0)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the bottom side by accelerating downward
	if (touchingEntity->bottomEdge + transform->ySpeed > _touchedRectangleTop &&
		touchingEntity->leftEdge  < _touchedRectangleRight &&
		touchingEntity->rightEdge > _touchedRectangleLeft &&
		transform->ySpeed > 0)
	{
		transform->ySpeed = 0;
	}

	// Scenario dealing with collision from the left side by accelerating leftward
	if (touchingEntity->leftEdge + transform->xSpeed < _touchedRectangleRight &&
		touchingEntity->topEdge  < _touchedRectangleBottom &&
		touchingEntity->bottomEdge > _touchedRectangleTop &&
		transform->xSpeed < 0)
	{
		transform->xSpeed = 0;
	}

	// Scenario dealing with collision from the top side by accelerating upward
	if (touchingEntity->topEdge + transform->ySpeed < _touchedRectangleBottom &&
		touchingEntity->leftEdge  < _touchedRectangleRight &&
		touchingEntity->rightEdge > _touchedRectangleLeft &&
		transform->ySpeed < 0)
	{
		transform->ySpeed = 0;
	}
}

void PhysicsSystem::CheckCollisionSides(ECS::Entity* touchingEntity, ECS::Entity* touchedEntity)
{

	if (std::find(
		touchedEntity->get<Tag>()->tagNames.begin(),
		touchedEntity->get<Tag>()->tagNames.end(),
		"Object")
		!=
		touchedEntity->get<Tag>()->tagNames.end())
	{
		if (std::find(
			touchingEntity->get<Tag>()->tagNames.begin(),
			touchingEntity->get<Tag>()->tagNames.end(),
			"Player")
			!=
			touchingEntity->get<Tag>()->tagNames.end())
		{
			/*if ((touchingEntity->get<BoxCollider>()->rightEdge)
				>
				(touchedEntity->get<BoxCollider>()->leftEdge))
			{
				touchedEntity->get<Transform>()->X += 1;
			}*/
			if ((touchingEntity->get<BoxCollider>()->leftEdge)
				<
				(touchedEntity->get<BoxCollider>()->rightEdge))
			{
				touchedEntity->get<Transform>()->X -= 1;
			}



			if ((touchingEntity->get<BoxCollider>()->bottomEdge)
				>
				(touchedEntity->get<BoxCollider>()->topEdge))
			{
				touchedEntity->get<Transform>()->Y += 1;
			}
			if ((touchingEntity->get<BoxCollider>()->topEdge)
				<
				(touchedEntity->get<BoxCollider>()->bottomEdge))
			{
				touchedEntity->get<Transform>()->Y -= 1;
			}

			/*
			if ((touchingEntity->get<Transform>()->X - touchingEntity->get<Transform>()->xSpeed)
				<
				(touchedEntity->get<Transform>()->X - touchingEntity->get<Transform>()->xSpeed))
			{
				touchedEntity->get<Transform>()->X += 1;
			}
			else if ((touchingEntity->get<Transform>()->X - touchingEntity->get<Transform>()->xSpeed)
				>
				(touchedEntity->get<Transform>()->X - touchingEntity->get<Transform>()->xSpeed))
			{
				touchedEntity->get<Transform>()->X -= 1;
			}

			if ((touchingEntity->get<Transform>()->Y - touchingEntity->get<Transform>()->ySpeed)
				<
				(touchedEntity->get<Transform>()->Y - touchingEntity->get<Transform>()->ySpeed))
			{
				touchedEntity->get<Transform>()->Y += 1;
			}
			else if ((touchingEntity->get<Transform>()->Y - touchingEntity->get<Transform>()->ySpeed)
				>
				(touchedEntity->get<Transform>()->Y - touchingEntity->get<Transform>()->ySpeed))
			{
				touchedEntity->get<Transform>()->Y -= 1;
			}
			*/
		}
	}
}

void PhysicsSystem::tick(ECS::World* world, float deltaTime)
{

	if (States::GetPausedState() == false)
	{
		world->each<BoxCollider, Sprite2D, Transform>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<BoxCollider> box,
				ECS::ComponentHandle<Sprite2D> sprite,
				ECS::ComponentHandle<Transform> transform) -> void
			{
				box->Update(transform->X, transform->Y, sprite->Image.getTextureRect().width, sprite->Image.getTextureRect().height);
			});




		world->each<Transform, BoxCollider>(
			[&](ECS::Entity* ent1,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<BoxCollider> box) -> void
			{
				world->each<TileMap>(
					[&](ECS::Entity* ent2,
						ECS::ComponentHandle<TileMap> tileMap) -> void
					{
						for (auto& x : tileMap->map)
						{
							for (auto& y : x)
							{
								for (auto& z : y)
								{
									if (z != nullptr)
									{

										// statement to avoid comapring same entity to itself
										if (ent1->getEntityId() != ent2->getEntityId())
										{
											if (z->GetCollision() == true)
											{
												if (IsColliding(box, z->shape,
													transform->xSpeed, transform->ySpeed))
												{
													// final collision check
													CheckCollisionSides(transform, box, z->shape);
												}
											}
										}
									}
								}
							}
						}
					});
			});





		//world->each<BoxCollider, Transform>(
		//	[&](ECS::Entity* ent1,
		//		ECS::ComponentHandle<BoxCollider> touchingBox,
		//		ECS::ComponentHandle<Transform> transform) -> void
		//	{
		//		world->each<BoxCollider>(
		//			[&](ECS::Entity* ent2,
		//				ECS::ComponentHandle<BoxCollider> touchedBox) -> void

		//			{

		//				// statement to avoid comparing same entity to itself
		//				if (ent1->getEntityId() != ent2->getEntityId())
		//				{
		//					// initial collision check
		//					if (IsColliding(touchingBox, touchedBox, transform->xSpeed, transform->ySpeed))
		//					{
		//						// final collsion check
		//						CheckCollisionSides(transform, touchingBox, touchedBox);
		//					}
		//				}

		//			});

		//	});

		world->each<BoxCollider, Transform, Tag>(
			[&](ECS::Entity* ent1,
				ECS::ComponentHandle<BoxCollider> touchingBox,
				ECS::ComponentHandle<Transform> transform1,
				ECS::ComponentHandle<Tag> tag1) -> void
			{
				world->each<BoxCollider, Transform, Tag>(
					[&](ECS::Entity* ent2,
						ECS::ComponentHandle<BoxCollider> touchedBox,
						ECS::ComponentHandle<Transform> transform2,
						ECS::ComponentHandle<Tag> tag2) -> void

					{

						// statement to avoid comparing same entity to itself
						if (ent1->getEntityId() != ent2->getEntityId())
						{
							// initial collision check
							if (IsColliding(touchingBox, touchedBox))
							{
								// final collsion check
								CheckCollisionSides(ent1, ent2);
							}
						}

					});

			});

		world->each<Transform>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<Transform> transform) -> void
			{
				transform->Move();
			});
	}
}
