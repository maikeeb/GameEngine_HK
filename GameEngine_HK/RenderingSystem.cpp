#include "Include/RenderingSystem.h"



RenderingSystem::RenderingSystem(void)
{

}

RenderingSystem::~RenderingSystem(void)
{

}

void RenderingSystem::tick(ECS::World* world, float deltaTime)
{
	// Clear the screen before drawing all textures
	if (States::GetPausedState() == false)
	{
		Engine::GetInstance().window->clear();


		

		// Lambda function
		world->each<Transform, Sprite2D>(
			[&](ECS::Entity* ent,
				ECS::ComponentHandle<Transform> transform,
				ECS::ComponentHandle<Sprite2D> sprite) -> void // no name
			{
				// add texture to unordered texture map
				if (textureMap.count(sprite->Texture) < 1)
				{
					textureMap[sprite->Texture] = LoadTexture(sprite->Texture);
				}

				// if no texture is found, add it
				if (sprite->Image.getTexture() == nullptr)
				{
					sprite->Image.setTexture(*textureMap[sprite->Texture]);
					sprite->Width = sprite->Image.getGlobalBounds().width;
					sprite->Height = sprite->Image.getGlobalBounds().height;
				}

				// update and draw to screen
				sprite->Image.setPosition(transform->X, transform->Y);
				Engine::GetInstance().window->draw(sprite->Image);
			});

		world->each<TileMap>(
			[&](ECS::Entity* entity,
				ECS::ComponentHandle<TileMap> tileMap)-> void
			{
				// loop through each tile and render onto the engine's window instance

				// note that this  is looping through a vector which stores a another, which stores the tile value
				for (auto& x : tileMap->map)
				{
					for (auto& y : x)
					{
						for (auto& z : y)
						{
							if (z != nullptr)
							{
								sf::RenderWindow* _window = Engine::GetInstance().window;
								_window->draw(z->shape);

								if (z->GetCollision() == true)
								{
									tileMap->collisionBox.setPosition(z->GetPosition());
									_window->draw(tileMap->collisionBox);
								}
							}
						}
					}
				}
			});

		//Display updates
		Engine::GetInstance().window->display();
	}
}


sf::Texture* RenderingSystem::LoadTexture(std::string texture)
{
	sf::Texture* _tex = new sf::Texture();

	// Exit the program by warning the user
	if (_tex->loadFromFile(texture) == NULL)
	{
		std::cerr << "Unable to load to load image " << texture << "./nIs this image the correct spelling or directory?" << std::endl;
		std::cerr << "Error" << std::endl;

		system("pause");

		exit(EXIT_FAILURE);
	}


	return _tex;
}