#pragma once

#include "ECS.h"
#include "Components.h"
#include "../States.h"

class MovementSystem :
	public ECS::EntitySystem
{
public:
	MovementSystem();
	~MovementSystem();
	void tick(ECS::World* world, float deltaTime) override;
};

