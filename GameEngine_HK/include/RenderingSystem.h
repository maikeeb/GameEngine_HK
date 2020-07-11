#pragma once

#include "ECS.h"
#include "Engine.h"
#include "Components.h"
#include <iostream>


class RenderingSystem : public ECS::EntitySystem
{
private:
	// Make a list with a dictionary-like key-value pairs with the speed of a hashmap (which would take in an object, string, to map its position in memory, where is stores a pointer to a texture)
	std::unordered_map<std::string, sf::Texture*> textureMap;

	sf::Texture* LoadTexture(std::string texture);

public:
	RenderingSystem(void);
	~RenderingSystem(void);

	void tick(ECS::World* world, float deltaTime) override;
};

