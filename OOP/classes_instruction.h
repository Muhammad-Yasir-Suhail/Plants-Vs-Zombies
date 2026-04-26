#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;
using namespace std;

class inst
{
	Texture texture;
	Sprite sprite;

	int time = 100;

public:

	inst(){
		texture.loadFromFile("assets/instructions/instruction_0.jpg");
		sprite.setPosition(0, 0);
		sprite.setTexture(texture);
	}

	bool update(RenderWindow& window, Event& event) {
		window.draw(sprite);
		static int page = 1;

		if (time-- <= 0 && (Keyboard::isKeyPressed(Keyboard::Space) )) {
			page++;

			time = 100;

			if (page > 4) {
				page = 0;
				return true;
			}

			texture.loadFromFile("assets/instructions/instruction_" + to_string(page) + ".jpg");

			sprite.setPosition(0, 0);
			sprite.setTexture(texture);
		}


		window.draw(sprite);

		return false;
	}
};

