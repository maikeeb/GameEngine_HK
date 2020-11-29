#pragma once

#include <iostream>
#include <sstream>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>



class Tile
{
public:
	bool bIsColliding;
	sf::RectangleShape shape;

	Tile();
	Tile(float xPos, float yPos, float gridSizeF, bool bIsColliding);
	~Tile();



	void Render(sf::RenderTarget& target);
	const bool& GetCollision() const; // cannot modify value when calling

	const sf::Vector2f& GetPosition() const;
	std::string ToString();
};

