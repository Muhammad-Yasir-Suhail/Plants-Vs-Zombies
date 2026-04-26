#include "classes_Zombies.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Zombie::update(RenderWindow& window) {
	static int timer = 0;
	if (spawnTime > timer++)
		return;
	// prints zombie on the window

	posx = (timer - spawnTime) * speed * -0.5 + 1000 - 90;

	animate(timer);

	texture.loadFromFile(imageFile);

	zombieSprite.setTexture(texture);
	zombieSprite.setPosition(posx, posy);

	window.draw(zombieSprite);

}

bool Zombie::hitBullet(int damage) {

	health -= damage;

	if (health <= 0) {
		return true;
	}
	return false;
}

bool Zombie::collisionZombie(int otherxStart, int otherxEnd, int otheryStart, int otheryEnd) {

	if (posx < otherxEnd && (posx + endx) > otherxStart && posy < otheryEnd && (posy + endy) > otheryStart) {

		return true;
	}
	return false;
}

void SimpleZombie::animate(int timer) {
	timer = timer % 1200;
	timer /= 100;

	imageFile = "assets/Zombies/NormalZombie/Zombie/Zombie_" + timer;
	imageFile += ".png";
}

void ZombieFactory::addZombie(int count, string* available, int availableSize) {
	Zombie** temp = new Zombie * [count + size];

	for (int i = 0; i < size; i++) {
		temp[i] = list[i];
	}

	for (int i = size; i < size + count; i++) {

		int random = rand() % availableSize;
		if (available[random] == "Simple Zombie")
			temp[i] = new SimpleZombie();
		else
			temp[i] = new Zombie();
	}

	delete[] list; // Free old memory
	list = temp;   // Update list with new memory
	size += count;
}

void ZombieFactory::update(RenderWindow& window) {
	for (int i = 0; i < size; i++) {
		list[i]->update(window);
	}
}