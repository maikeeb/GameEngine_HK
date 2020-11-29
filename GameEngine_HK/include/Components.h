#pragma once


// #include "Engine.h"
#include <SFML\Graphics.hpp>
#include "ECS.h"
#include "Tile.h"
#include <fstream>

struct Transform
{
public:
	ECS_DECLARE_TYPE;

	float X, Y;
	
	float xSpeed, ySpeed;
	float Rotation;
	float Gravity;

	bool bHasGravity;
	bool bIsOnFloor;


	Transform(float x, float y) :X(x), Y(y)
	{
		xSpeed = 0.0f;
		ySpeed = 0.0f;


		Rotation = 0.0f;
		Gravity = 0.0f;

		bHasGravity = false;
		bIsOnFloor = false;
	}

	void Move()
	{
		X += xSpeed;
		Y += ySpeed;
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


struct InputController
{
public:
	ECS_DECLARE_TYPE;
	
	bool bIsControllerActive;

	bool wKey, aKey, sKey, dKey;
	//bool upKey, leftKey, downKey, rightKey;

	InputController()
	{
		bIsControllerActive = true;

		wKey = false;
		aKey = false;
		sKey = false;
		dKey = false;

		/*upKey = false;
		leftKey = false;
		rightKey = false;
		downKey = false;*/
	}


};
ECS_DEFINE_TYPE(InputController);


struct BoxCollider
{
public:
	ECS_DECLARE_TYPE;

	int leftEdge, rightEdge, topEdge, bottomEdge;

	BoxCollider() {
		leftEdge = 0;
		rightEdge = 0;
		topEdge = 0;
		bottomEdge = 0;
	}

	void Update(int xSide, int ySide, int width, int height) {
		leftEdge = xSide;
		rightEdge = xSide + width;

		topEdge = ySide;
		bottomEdge = ySide + height;
	}
};

ECS_DEFINE_TYPE(BoxCollider);

struct Camera
{
public:
	ECS_DECLARE_TYPE;

	sf::View cameraView;

	Camera(sf::Vector2f pivot)
	{
		cameraView.setCenter(pivot);
	}
};

ECS_DEFINE_TYPE(Camera);

struct TileMap
{
	ECS_DECLARE_TYPE;

	float gridSizeF; // You can change this value to increase the size of the whole grid for more tile insertion
	unsigned int gridSizeU;
	unsigned int layers; // layers value used for rendering in a certain order (see constructor_

	sf::Vector2u maxSize; // vector to set the size of each tile
	sf::RectangleShape collisionBox;


	/**
	'map' structure 
	- 1st vector represents a column of vectors
	- 2nd vector represents a row of vectors
	- 3rd vector represents a layer of Tile pointers
	*/
	std::vector<std::vector<std::vector<Tile*>>> map;

	TileMap()
	{
		this->gridSizeF = 50.0f;
		this->gridSizeU = static_cast<unsigned int>(this->gridSizeF);

		this->maxSize.x = 20; //number of tiles wide (size of tiles is given by gridsize)
		this->maxSize.y = 20; // number of tiles high 

		this->layers = 1;
		this->map.resize(this->maxSize.x);
		for (size_t x = 0; x < this->maxSize.x; x++)
		{
			this->map.push_back(std::vector<std::vector<Tile*>>());

			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y);
				this->map[x].push_back(std::vector<Tile*>());
				for (size_t z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers);
					this->map[x][y].push_back(nullptr);
				}
			}
		}

		this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
		this->collisionBox.setFillColor(sf::Color(0, 255, 0, 50));
		this->collisionBox.setOutlineColor(sf::Color::Green);
		this->collisionBox.setOutlineThickness(-1.0f);


	}

	~TileMap()
	{
		Clear();
	}
	void AddTile(const unsigned int X_COL, const unsigned int Y_ROW, const unsigned int Z_ORDER, bool bHasCollision)
	{
		if (X_COL < this->maxSize.x && X_COL >= 0 &&
			Y_ROW < this->maxSize.y && Y_ROW >= 0 &&
			Z_ORDER < this->layers && Z_ORDER >= 0)
		{
			if (this->map[X_COL][Y_ROW][Z_ORDER] == nullptr)
			{
				this->map[X_COL][Y_ROW][Z_ORDER] = new Tile(X_COL, Y_ROW, this->gridSizeF, bHasCollision);
				
				std::cout << "Added" << std::endl;
			}
		}
	}

	void Clear()
	{
		for (int x = 0; x < maxSize.x; x++)
		{
			for (int y = 0; y < maxSize.y; y++)
			{
				for (int z = 0; z < layers; z++)
				{
					delete this->map[x][y][z];
					this->map[x][y][z] = NULL;
				}

				this->map[x][y].clear();
			}

			this->map[x].clear();
		}

		this->map.clear();
	}

	void SaveTileMap(std::string fileName)
	{
		std::ofstream _saveFile;
		_saveFile.open(fileName);

		if (_saveFile.is_open() == true)
		{
			_saveFile << maxSize.x << " " << maxSize.y << "\n"
				<< gridSizeF << "\n"
				<< layers << "\n";

			for (int x = 0; x < maxSize.x; x++)
			{
				for (int y = 0; y < maxSize.y; y++)
				{
					for (int z = 0; z < layers; z++)
					{
						if (this->map[x][y][z] != nullptr)
						{
							_saveFile << x << " " << y << " " << z << " " << this->map[x][y][z]->ToString() << "\n";
						}

						
					}
				}
			}

				
		}
		else
		{
			std::cout << "Error: TileMap could not save to file" << fileName << std::endl;
		}
		_saveFile.close();
	}

	void LoadTileMap(std::string fileName)
	{
		std::ifstream _loadFile;
		_loadFile.open(fileName);

		if (_loadFile.is_open() == true)
		{
			sf::Vector2f _size;
			float _gridSizeF = 0;
			unsigned int _layers = 0;
			unsigned int _x = 0;
			unsigned int _y = 0;
			unsigned int _z = 0;
			bool _bHasCollision = false;

			_loadFile >> _size.x >> _size.y >> _gridSizeF >> _layers;
			


			std::cout << _size.x << " is the size.x value, " << _size.y << " is the size.y value, " << _gridSizeF << " is the gridsize, " << _layers << " is the layers value" << std::endl;

			this->gridSizeF = _gridSizeF;
			this->gridSizeU = static_cast<unsigned int>(this->gridSizeF);
			this->maxSize.x = _size.x;
			this->maxSize.y = _size.y;
			this->layers = _layers;

			this->Clear();

			this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());

			for (int x = 0; x < maxSize.x; x++)
			{
				for (int y = 0; y < maxSize.y; y++)
				{
					this->map[x].resize(this->maxSize.y, std::vector<Tile*>());
					for (int z = 0; z < layers; z++)
					{
						this->map[x][y].resize(this->layers, NULL);

					}
				}
			}


			while (_loadFile >> _x >> _y >> _z >> _bHasCollision)
			{
				std::cout << _x << ", " << _y << ", " << _z << std::endl;
				this->map[_x][_y][_z] = new Tile(_x, _y, _gridSizeF, _bHasCollision);
			}



		}
		else
		{
			std::cout << "Error: TileMap could not load file" << fileName << std::endl;
		}
		_loadFile.close();
	}
};
ECS_DEFINE_TYPE(TileMap);

struct Tag
{
public:
	ECS_DECLARE_TYPE;
	std::vector<std::string> tagNames;

	Tag()
	{}

	void AddTag(std::string tag)
	{
		tagNames.push_back(tag);
	}
};
ECS_DEFINE_TYPE(Tag);
