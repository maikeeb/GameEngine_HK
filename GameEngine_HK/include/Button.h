#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>


class Button
{
public:
	sf::RectangleShape buttonBG;
	sf::Text buttonText;

	bool bIsPressed, bIsReleased, bIsClicked, bIsHighlighted;


	Button();
	Button(sf::Vector2f size, sf::Color color, std::string text);
	~Button();
	bool IsHighlighted();

	void HighLight(sf::RenderWindow* window);
	void Update(sf::Event event, float deltaTime);
	void Render(sf::RenderWindow* window, float deltaTime);
	void CheckPressed(sf::Event event);

private:
	sf::Color defaultColor;
	sf::Color highlightedColor;
};

