
#ifndef CLASSES_LEVELS_H
#define CLASSES_LEVELS_H


#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "classes_Cards.h"
#include "classes_Lawn.h"
#include "classes_Zombies.h"
#include "classes_Plants.h"


//stores programs

using namespace std;
using namespace sf;



class Level{
protected:
	Level() {

		time = 0;
		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";
		count = 0;
		plantSize = 0;
		plantAvailable = nullptr;



		zombieSize = 0;
		zombieAvailable = nullptr;

		lawn = Lawn::Instance();
		
	}

	Level(const Level&) = delete;
	Level& operator=(const Level&) = delete;


	int time;
	int count;
	string spriteImage;
	Sprite sprite;
	Texture texture;
	string* plantAvailable;
	int plantSize;
	string* zombieAvailable;
	int zombieSize;

	Cards card;
	
	Lawn* lawn;

	ZombieFactory* zombie;

	PlantFactory* plant;


	
public:
	static Level* Instance() {
		static Level instance;

		return &instance;
	}

	virtual void update(RenderWindow& window, int& scores);

	void checkCollisions();

	void pause(RenderWindow& window);

	bool endLevel() {

		if (zombie->getSize() == 0)
		{

			cout << "no more zombies";
			return true;
		}

		return false;
	}

	~Level() {
		delete[] plantAvailable;

		delete plant;
		delete zombie;

		delete lawn;
	}

	virtual string checkWin() {
		if (zombie->ateBrain())
			return "lost";
		return "\0";
	}
};

class Level1 : public Level {
protected:
	Level1() {

		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";
		texture.loadFromFile(spriteImage);
		sprite.setTexture(texture);
		sprite.setPosition(1000, 10);
		count = 1;
		plantSize = 2;
		plantAvailable = new string[plantSize];

		plantAvailable[0] = "sunflower";
		plantAvailable[1] = "peashooter";

		zombieSize = 1;
		zombieAvailable = new string[zombieSize];

		zombieAvailable[0] = "Simple Zombie";

		card.addPlants(plantAvailable, plantSize);

		zombie = ZombieFactory::Instance();

		zombie->addZombie(15, zombieAvailable, zombieSize);

		plant = PlantFactory::Instance();

	}

	Level1(const Level1&) = delete;
	Level1& operator=(const Level1&) = delete;

public:
	static Level1* Instance() {
		static Level1 instance;

		return &instance;
	}

	
};

class Level2 : public Level {
protected:
	Level2() {

		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";
		texture.loadFromFile(spriteImage);
		sprite.setTexture(texture);
		sprite.setPosition(1000, 10);
		count = 1;
		plantSize = 4;
		plantAvailable = new string[plantSize];

		plantAvailable[0] = "sunflower";
		plantAvailable[1] = "peashooter";
		plantAvailable[2] = "cherrybomb";
		plantAvailable[3] = "wallnut";

		zombieSize = 3;
		zombieAvailable = new string[zombieSize];

		zombieAvailable[0] = "Simple Zombie";
		zombieAvailable[1] = "Football Zombie";
		zombieAvailable[2] = "Dancing Zombie";

		zombie = ZombieFactory::Instance();

		zombie->addZombie(25, zombieAvailable, zombieSize);

		plant = PlantFactory::Instance();

	}

	Level2(const Level2&) = delete;
	Level2& operator=(const Level2&) = delete;

public:
	static Level2* Instance() {
		static Level2 instance;

		return &instance;
	}

	void update(RenderWindow& window, int& scores) {
		static int i = 0;
		if (i == 0) {
			card.addPlants(plantAvailable, plantSize);
			i = 1;
		}

		Level::update(window, scores);
	}


};

class Level3 : public Level {
protected:
	Level3() {

		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";
		texture.loadFromFile(spriteImage);
		sprite.setTexture(texture);
		sprite.setPosition(1000, 10);
		count = 1;
		plantSize = 6;
		plantAvailable = new string[plantSize];

		plantAvailable[0] = "sunflower";
		plantAvailable[1] = "peashooter";
		plantAvailable[2] = "cherrybomb";
		plantAvailable[3] = "wallnut";
		plantAvailable[4] = "snowpea";
		plantAvailable[5] = "repeaterpea";
		//plantAvailable[6] = "shovel";

		zombieSize = 3;
		zombieAvailable = new string[zombieSize];

		zombieAvailable[0] = "Simple Zombie";
		zombieAvailable[1] = "Football Zombie";
		zombieAvailable[2] = "Dancing Zombie";

		card.addPlants(plantAvailable, plantSize);

		zombie = ZombieFactory::Instance();

		zombie->addZombie(30, zombieAvailable, zombieSize);

		plant = PlantFactory::Instance();

	}

	Level3(const Level3&) = delete;
	Level3& operator=(const Level3&) = delete;

public:
	static Level3* Instance() {
		static Level3 instance;

		return &instance;
	}

	void update(RenderWindow& window, int& scores) {
		static int i = 0;
		if (i == 0) {
			card.addPlants(plantAvailable, plantSize);
			i = 1;
		}

		Level::update(window, scores);
	}


};

class Level4 : public Level {
protected:

	Texture fogT;

	Sprite fog;

	Level4() {

		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";
		texture.loadFromFile(spriteImage);
		sprite.setTexture(texture);
		sprite.setPosition(1000, 10);
		count = 1;
		plantSize = 6;
		plantAvailable = new string[plantSize];

		plantAvailable[0] = "sunflower";
		plantAvailable[1] = "peashooter";
		plantAvailable[2] = "cherrybomb";
		plantAvailable[3] = "wallnut";
		plantAvailable[4] = "snowpea";
		plantAvailable[5] = "repeaterpea";
		//plantAvailable[6] = "shovel";

		zombieSize = 3;
		zombieAvailable = new string[zombieSize];

		zombieAvailable[0] = "Simple Zombie";
		zombieAvailable[1] = "Football Zombie";
		zombieAvailable[2] = "Dancing Zombie";

		card.addPlants(plantAvailable, plantSize);

		zombie = ZombieFactory::Instance();

		zombie->addZombie(30, zombieAvailable, zombieSize);

		plant = PlantFactory::Instance();

		fogT.loadFromFile("assets/Background/fog.png");
		fog.setTexture(fogT);
		fog.setPosition(650, 0);

	}

	Level4(const Level4&) = delete;
	Level4& operator=(const Level4&) = delete;

public:
	static Level4* Instance() {
		static Level4 instance;

		return &instance;
	}

	void update(RenderWindow& window, int& scores) {
		Level::update(window, scores);

		window.draw(fog);
	}

	string checkWin() {
		if (zombie->ateBrain())
			return "lost";

		else if (endLevel()) {
			return "win";
		}
		return "\0";
	}


};

#endif