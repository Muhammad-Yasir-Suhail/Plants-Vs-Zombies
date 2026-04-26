#include "classes_Lawn.h"
#include "SFML/Graphics.hpp"
#include <iostream>

const int pixelx = 1000;

void Lawn::update(RenderWindow& window) {bool collisionLawn(int otherxStart, int otherxEnd, int otheryStart, int otheryEnd);

	int y = 80;

	for (int i = 0; i < size; i++) {

		if (mover[i] == "stop") {
			imageFile = "assets/Inventory-GameScreen/car.png";

			texture.loadFromFile(imageFile);
			sprite.setTexture(texture);
			sprite.setPosition(180, y);
			window.draw(sprite);

		}
		else if (mover[i] == "attack") {
			int x = timer[i]++ * 2 + 180;
			imageFile = "assets/Inventory-GameScreen/car.png";

			texture.loadFromFile(imageFile);
			sprite.setTexture(texture);
			sprite.setPosition(x, y);
			window.draw(sprite);
			

			if (x > pixelx) {
				mover[i] = "dead";
			}
		}

		y += 100;
		
	}

}

bool Lawn::collisionLawnZombie(int* coordinatesZombie) {

	for (int i = 0; i < size; i++) {
		int x = timer[i] * 2 + 180;
		int y = 80 + i * 100;
		if (coordinatesZombie[0] <= x + 10 && coordinatesZombie[1] <= y + 10 && coordinatesZombie[2] >= x && coordinatesZombie[3] >= y) {


			if (mover[i] == "stop") {
				mover[i] = "attack";
				
			}
			return true;
		}
	}

	return false;
}

void Lawn::draw(RenderWindow& window){
	int y = 80;

	for (int i = 0; i < size; i++) {

		if (mover[i] == "stop") {
			imageFile = "assets/Inventory-GameScreen/car.png";

			texture.loadFromFile(imageFile);
			sprite.setTexture(texture);
			sprite.setPosition(180, y);
			window.draw(sprite);

		}
		else if (mover[i] == "attack") {
			int x = timer[i] * 2 + 180;
			imageFile = "assets/Inventory-GameScreen/car.png";

			texture.loadFromFile(imageFile);
			sprite.setTexture(texture);
			sprite.setPosition(x, y);
			window.draw(sprite);


			if (x > pixelx) {
				mover[i] = "dead";
			}
		}

		y += 100;

	}
}