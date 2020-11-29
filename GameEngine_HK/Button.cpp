#include "include/Button.h"

Button::Button()
{
}

Button::Button(sf::Vector2f size, sf::Color color, std::string text)
{
	bIsPressed = false;
	bIsReleased = false;
	bIsClicked = false;
	bIsHighlighted = false;

	defaultColor = sf::Color(color);
	highlightedColor = sf::Color(defaultColor.r + 50, defaultColor.g + 50, defaultColor.b + 50);

	buttonBG.setSize(size);
	buttonBG.setFillColor(defaultColor);
	buttonBG.setPosition(sf::Vector2f(0, 0));

	buttonText.setCharacterSize(12);
	buttonText.setFillColor(sf::Color::White);
	buttonText.setPosition(sf::Vector2f(0, 0));
	buttonText.setString(text);
}

Button::~Button()
{
}

bool Button::IsHighlighted()
{
	return bIsHighlighted;
}

void Button::HighLight(sf::RenderWindow* window)
{
	if (buttonBG.getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
	{
		buttonBG.setFillColor(sf::Color(highlightedColor));
		this->bIsHighlighted = true;
	}
	else
	{
		buttonBG.setFillColor(sf::Color(defaultColor));
		this->bIsHighlighted = false;
	}
}

void Button::Update(sf::Event event, float deltaTime)
{
	CheckPressed(event);
}

void Button::Render(sf::RenderWindow* window, float deltaTime)
{
	window->draw(buttonBG);
	window->draw(buttonText);
	window->display();
}

void Button::CheckPressed(sf::Event event)
{
	if (this->bIsHighlighted)
	{
		//if (event.type == sf::Mouse::isButtonPressed(sf::Mouse::Left))
		if (event.type== sf::Event::MouseButtonPressed)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				this->bIsPressed = true;
			}
			else
			{
				bIsPressed = false;
				bIsClicked = false;
			}
		}
		
	}
	if (this->bIsPressed)
	{
		if (event.type == sf::Event::MouseButtonReleased)
		{
			this->bIsReleased = true;
			this->bIsClicked = true;
		}

	}
	else
	{
		this->bIsReleased = false;
		this->bIsClicked = false;
	}
}
