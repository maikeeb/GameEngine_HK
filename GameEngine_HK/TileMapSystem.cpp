#include "include/TileMapSystem.h"

TileMapSystem::TileMapSystem()
{
}

TileMapSystem::~TileMapSystem()
{
}

void TileMapSystem::tick(ECS::World* world, float deltaTime)
{
	Engine::GetInstance().world->each<TileMap>(
		[&](ECS::Entity* entity,
			ECS::ComponentHandle<TileMap> tileMap) -> void
	{

		/*
		- If mouse is left-clicked then generate a tile at the specified x, y location of the cursor in a grid	like order
		- If mouse is right-clicked then generate a just like when left-clicked but without the collider
		- Tile will only be generated if the area under the mouse doesn't have an existing tile value
		- You can increase the size of the grid in the tilemap component found in the "Components.h"
		*/

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				AddTileOnClick(true, tileMap);
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			{
				AddTileOnClick(false, tileMap);
			}


			if (ButtonMap::GetMap()["SAVE"]->bIsClicked == true)
			{
				std::cout << "Saved" << std::endl;

				tileMap->SaveTileMap("TileTest.txt");

				ButtonMap::GetMap()["SAVE"]->bIsClicked = false;
			}

			if (ButtonMap::GetMap()["LOAD"]->bIsClicked == true)
			{
				std::cout << "Loaded" << std::endl;

				tileMap->LoadTileMap("TileTest.txt");

				ButtonMap::GetMap()["LOAD"]->bIsClicked = false;
			}
	});

}

void TileMapSystem::AddTileOnClick(bool bHasCollision, ECS::ComponentHandle<TileMap> tileMap)
{
	// Reference for a window pointer that is sused below to determine active
	// cursor position for adding tiles

	sf::RenderWindow* _windRef = Engine::GetInstance().window;
	sf::Vector2f _mousePosView = _windRef->mapPixelToCoords(sf::Mouse::getPosition(*_windRef));

	sf::Vector2i _mousePosGrid(
		static_cast<int>(_mousePosView.x) / static_cast<int>(tileMap->gridSizeF),
		static_cast<int>(_mousePosView.y) / static_cast<int>(tileMap->gridSizeF)
	);

	tileMap->AddTile(_mousePosGrid.x, _mousePosGrid.y, 0, bHasCollision);

	
}
