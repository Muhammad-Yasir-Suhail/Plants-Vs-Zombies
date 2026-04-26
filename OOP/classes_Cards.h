#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;
using namespace sf;
class Cards{

	string* plant;
	string* image;
	int size;
	bool* selected;

	Sprite sprite;
	Texture texture;

public:
	Cards(){
		size = 0;
		image = new string[8];
		selected = new bool[8];
		plant = new string[8];

	}

	void addPlants(string* plants, int s) {

		for (int i = 0; i < s; i++) {
			plant[i] = plants[i];
			image[i] = "assets/Inventory-GameScreen/Cards/card_" + plants[i] + ".png"; ;
			selected[i] = false ;
		}

		size = s;
	}

	string isPlantSelected(){
		for (int i = 0; i < size; i++) {
			if (selected[i])
				return plant[i];
		}

		return "0";
	}

	void displayCards(RenderWindow& window, int time, int& scores) {

		Sprite sprite;
		Texture texture;
		int x = 75;
		float scalex = 55.0f / 65.0f;
		float scaley = 70.0f / 90.0f;

		if (Keyboard::isKeyPressed(Keyboard::Num1 )&&scores>=50) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
				
			}
			scores -= 50;
			selected[0] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2) && scores >= 100) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
				
			}
			scores -= 100;
			selected[1] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3)&&scores>=150) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
			}
			scores -= 150;
			selected[2] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4)&&scores>=50) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
			}
			scores -= 50;

			selected[3] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num5)&&scores>=150) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
			}
			scores -= 150;
			selected[4] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num6)&&scores>=200) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
				
			}
			scores -= 200;

			selected[5] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num7)) {
			for (int i = 0; i < size; i++) {
				selected[6] = 0;
			}

			selected[6] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num8)) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
			}

			selected[0] = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num0)) {
			for (int i = 0; i < size; i++) {
				selected[i] = 0;
			}
		}


		for (int i = 0; i < size; i++) {

			texture.loadFromFile(image[i]);
			sprite.setTexture(texture);

			sprite.setScale(scalex, scaley);

			sprite.setPosition(x, 10);
			window.draw(sprite);
			if (selected[i]) {
				if (selected[i])
				{
					sprite.setPosition(Mouse::getPosition(window).x - 40, Mouse::getPosition(window).y - 50);
					if (Keyboard::isKeyPressed(Keyboard::Space)) {
						selected[i] = 0;

					}


					window.draw(sprite);
				}
			}


			x += 65;

		}
	}

	void draw(RenderWindow& window) {
		Sprite sprite;
		Texture texture;
		int x = 75;
		float scalex = 55.0f / 65.0f;
		float scaley = 70.0f / 90.0f;

		for (int i = 0; i < size; i++) {

			texture.loadFromFile(image[i]);
			sprite.setTexture(texture);

			sprite.setScale(scalex, scaley);

			sprite.setPosition(x, 10);
			window.draw(sprite);

			x += 65;

		}
	}

	~Cards()
	{
		if (selected != nullptr)
		delete[] selected;
		if (plant != nullptr)
		delete[] plant;
		if (image != nullptr)
		delete[] image;
	}

};

