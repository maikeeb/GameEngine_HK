#include "include/Tile.h"

Tile::Tile()
{
}

Tile::Tile(float xPos, float yPos, float gridSizeF, bool bIsColliding)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::Red);
	this->shape.setPosition(xPos * gridSizeF, yPos * gridSizeF);

	this->bIsColliding = bIsColliding;
}

Tile::~Tile()
{
}

void Tile::Render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}

const bool& Tile::GetCollision() const
{
	return this->bIsColliding;
}

const sf::Vector2f& Tile::GetPosition() const
{
	return this->shape.getPosition();
}

std::string Tile::ToString()
{

	std::stringstream _stringForm;
	_stringForm << this->bIsColliding << " ";
	return _stringForm.str();
}
