//game main

#include <SFML\Graphics.hpp>
#include "../GameEngine_HK/include/AnimationSystem.h"
#include "../GameEngine_HK/include/Engine.h"

int main(int argc, char* args[])
{

	// declare and get instance of singleton
	Engine& gameEngine = Engine::GetInstance();

	sf::RenderWindow window(sf::VideoMode(800, 600), "GameEngine");

	// Create world fro attaching entities and system to
	gameEngine.world = ECS::World::createWorld();
	ECS::Entity* background; // create it in memory
	ECS::Entity* guy;
	

	// Add the systems to the engine
	gameEngine.AddSystem(new RenderingSystem());
	gameEngine.AddSystem(new AnimationSystem());

	


	background = gameEngine.world->create(); //put it in the world/window
	guy = gameEngine.world->create();

	


	// assign components to entities after creation

	background->assign<Transform>(0, 0);
	background->assign<Sprite2D>("../Debug/Images/bg.jpg");


	guy->assign<Transform>(25, 32);
	guy->assign<Sprite2D>("../Debug/Images/herosheet.png");
	guy->assign<Animator>(32, 32, 1000.0f); // width, height, and the time between the frames
	std::cout << guy->getEntityId() << " is the entity ID." << std::endl;
	std::cout << background->getEntityId() << " is the entity ID." << std::endl;

	// Pass the window's reference to the engine and start
	gameEngine.Start(&window);


	return 0;

}