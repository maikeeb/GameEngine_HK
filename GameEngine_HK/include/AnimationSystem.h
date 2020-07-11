#pragma once

#include "ECS.h"
#include "Components.h"
#include "Engine.h"

class AnimationSystem : public ECS::EntitySystem
{
private:

	void tick(ECS::World* world, float deltaTime) override;

public:
	AnimationSystem();
	~AnimationSystem();

};

