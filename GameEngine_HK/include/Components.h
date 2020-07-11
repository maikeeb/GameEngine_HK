#pragma once


#include "Engine.h"
#include <SFML\Graphics.hpp>
#include "ECS.h"


struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float X;
	float Y;
	float Rotation;


	Transform(float x, float y)
	{
		X = x;
		Y = y;
		Rotation = 0.0f;
	}
};

ECS_DEFINE_TYPE(Transform);

struct Sprite2D
{
public:
	ECS_DECLARE_TYPE;

	sf::Sprite Image;
	std::string Texture;

	int Width;
	int Height;

	Sprite2D(std::string name)
	{
		Texture = name;
	}

};
ECS_DEFINE_TYPE(Sprite2D);



struct Animator
{
public:
	ECS_DECLARE_TYPE;

	int spriteWidth, spriteHeight;
	int currentColumn, currentRow;
	float currentTime, nextFrameTime;

	Animator(int width, int height, float timeBetweenFrames) 
	{
		spriteWidth = width;
		spriteHeight = height;

		currentColumn = 0;
		currentRow = 0;

		nextFrameTime = timeBetweenFrames;

		currentTime = 0;

	}

};
ECS_DEFINE_TYPE(Animator);