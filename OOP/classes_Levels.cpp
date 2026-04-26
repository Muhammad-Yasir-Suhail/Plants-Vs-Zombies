#include "classes_Levels.h"
#include "SFML/Graphics.hpp"
#include <iostream>

void Level::update(RenderWindow& window, int& scores) {


	if (time % 800 < 200)
		spriteImage = "assets/Inventory-GameScreen/Adventure_1.png";
	else
		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";

	texture.loadFromFile(spriteImage);
	sprite.setTexture(texture);
	sprite.setPosition(1000, 10);

	window.draw(sprite);


	// checks if any plant is selected by the user

	string selectedPlant = card.isPlantSelected();

	if (selectedPlant != "0" && Keyboard::isKeyPressed(Keyboard::Space)) {
		plant->createPlant(selectedPlant, Mouse::getPosition(window).x, Mouse::getPosition(window).y);
	}

	if (time > 150) {

		card.displayCards(window, time, scores);
		lawn->update(window);
		zombie->update(window);
		plant->update(window,scores);
		checkCollisions();

	}
	time++;

}


void Level::checkCollisions() {
	
	zombie->checkCollisionPlant();
	//check collision of zombie with lawn
	for (int i = 0; i < zombie->getSize(); i++) {

		int* cordinates = zombie->getCoordinates(i);

		bool collision = lawn->collisionLawnZombie(cordinates);

		

		if (collision) {
			zombie->killed(i);
		}

	}
}

void Level::pause(RenderWindow& window) {
	if (time % 800 < 200)
		spriteImage = "assets/Inventory-GameScreen/Adventure_1.png";
	else
		spriteImage = "assets/Inventory-GameScreen/Adventure_0.png";

	texture.loadFromFile(spriteImage);
	sprite.setTexture(texture);
	sprite.setPosition(1000, 10);

	window.draw(sprite);


	// checks if any plant is selected by the user

	if (time > 150) {

		card.draw(window);
		lawn->draw(window);
		zombie->draw(window);
		plant->draw(window);

	}
}