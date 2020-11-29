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
	ECS::Entity* tux;


	// Add the systems to the engine
	gameEngine.AddSystem(new RenderingSystem());
	gameEngine.AddSystem(new AnimationSystem());
	gameEngine.AddSystem(new InputSystem(&window));
	gameEngine.AddSystem(new MovementSystem());
	gameEngine.AddSystem(new TileMapSystem());
	gameEngine.AddSystem(new PhysicsSystem());



	background = gameEngine.world->create(); //put it in the world/window
	guy = gameEngine.world->create();
	tux = gameEngine.world->create();





	// assign components to entities after creation
	background->assign<Transform>(0, 0);
	background->assign<Sprite2D>("../Debug/Images/bg.jpg");
	background->assign<TileMap>();

	tux->assign<Transform>(100, 32);
	tux->assign<Sprite2D>("../Debug/Images/tux_from_linux.png");
	tux->assign<BoxCollider>();
	tux->assign<Animator>(32, 32, 1400.0f);
	tux->assign<Tag>();
	tux->get<Tag>()->AddTag("Object");
	//tux->assign<TileMap>();

	guy->assign<Transform>(25, 32);
	guy->assign<Sprite2D>("../Debug/Images/herosheet.png");
	guy->assign<Animator>(32, 32, 1000.0f); // width, height, and the time between the frames
	guy->assign<InputController>();
	//guy->assign<TileMap>();
	guy->assign<Camera>(sf::Vector2f(window.getSize().x / 2, window.getSize().y / 2));
	guy->assign<BoxCollider>();
	guy->assign<Tag>();
	guy->get<Tag>()->AddTag("Player");


	std::cout << guy->getEntityId() << " is the entity ID." << std::endl;
	//std::cout << background->getEntityId() << " is the entity ID." << std::endl;

	// Pass the window's reference to the engine and start


	gameEngine.Start(&window);


	return 0;

}