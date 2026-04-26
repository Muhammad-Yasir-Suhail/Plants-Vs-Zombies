#pragma once

#ifndef CLASSES_ZOMBIES_H
#define CLASSES_ZOMBIES_H

#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

// stores all the classes data

using namespace std;
using namespace sf;

class Zombie {
protected:

	float slow ;
	float check ;
	float head;
	float timer;
	int spawnTime;
	string name;
	int health;
	int posx;
	int posy;
	int endx;
	int endy;
	string state;
	int hitPower;
	String imageFile;
	Sprite zombieSprite;
	Texture texture;
	

public:
	Zombie() {

		check = 0;
		head = 0;
		slow = 0;
		timer = 0;
		state = "wait";
		health = 100;
		posx = 1180;
		posy = (rand() % 5) * 95 + 50;
		endx = 40;
		endy = 65;
		hitPower = 0;
		imageFile = "assets/Zombies/NormalZombie/Zombie/Zombie_0.png";

		static int timerDefault = 0;

		spawnTime = timerDefault++ * (rand() % 30 + 20) +50;

		texture.loadFromFile(imageFile);
		zombieSprite.setTexture(texture);
	}

	virtual void animate(RenderWindow& window);

	virtual void update(RenderWindow& window);
	
	virtual int getX() { return posx; }
	
	virtual int getY() { return posy; }

	virtual int getWidth() { return endx; }

	virtual int getHeight() { return endy; }

	int getDamage() { return hitPower; }

	virtual string checkState();
	
	virtual bool hitBullet(int damage);
	
	virtual bool collisionZombie(int otherxStart, int otherxEnd, int otheryStart, int otheryEnd);

	virtual void killed();

	virtual bool checkKilled();

	virtual void stopped() { state = "stop"; }

	virtual void move() { state = "move"; }

	virtual void died() { state = "died"; }

	virtual void death() { state = "death"; }

	virtual void slowed() { slow = 50; }

	virtual void draw(RenderWindow& window);

};

class SimpleZombie: public Zombie{
	
public:
	SimpleZombie(){

		health = 180;
		endx = 52;
		endy = 85;
		hitPower = 20;
		
		texture.loadFromFile(imageFile);
		zombieSprite.setTexture(texture);
	}	

	SimpleZombie(int x, int y) {

		health = 180;
		endx = 52;
		endy = 85;
		hitPower = 20;

		posx = x;
		posy = y;

		texture.loadFromFile(imageFile);
		zombieSprite.setTexture(texture);
	}

	void animate(RenderWindow& window);

	void update(RenderWindow& window) {
		Zombie::update(window);
	}
};

class FootballZombie : public Zombie {

public:
	FootballZombie() {

		health = 550;
		endx = 52;
		endy = 85;
		hitPower = 100;

		texture.loadFromFile(imageFile);
		zombieSprite.setTexture(texture);
	}

	void animate(RenderWindow& window);
};

class DancingZombie : public Zombie {

protected:
	int oldy;
	int changeTimer;
public:
	DancingZombie() {
		endx = 52;
		endy = 85;
		hitPower = 100;
		oldy = posy;
		changeTimer = rand() % 100 + 100;

		texture.loadFromFile(imageFile);
		zombieSprite.setTexture(texture);
	}

	virtual void update(RenderWindow& window);

	void animate(RenderWindow& window);


};

class ZombieFactory {
protected:
	Zombie** list;
	int size;

	ZombieFactory() {

		list = nullptr;
		size = 0;

	}

	ZombieFactory(const ZombieFactory&) = delete;
	ZombieFactory& operator=(const ZombieFactory&) = delete;

public:

	static ZombieFactory* Instance() {
		static ZombieFactory* instance = new ZombieFactory;

		return instance;
	}

	int getSize() { return size; }

	void addZombie(int count, string* available, int availableSize);

	void update(RenderWindow& window);

	int* getCoordinates(int num);

	void killed(int num);

	void died(int num);

	void checkCollisionPlant();

	void draw(RenderWindow& window);

	bool ateBrain();

	friend class Pea;

	~ZombieFactory() {
		if (size > 0) {
			for (int i = 0; i < size; i++) {
				delete list[i];
			}
		}

		delete[] list;
	}

};

#endif