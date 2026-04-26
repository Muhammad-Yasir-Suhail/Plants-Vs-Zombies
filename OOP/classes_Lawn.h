#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

using namespace std;
using namespace sf;

class Lawn {


protected:

	Lawn() {
		mover = new string[size];
		timer = new int[size];
		for (int i = 0; i < size; i++) {
			mover[i] = "stop";
			timer[i] = 0;
		}

		
	}



	string imageFile;
	Texture texture;
	Sprite sprite;

	string* mover;
	int* timer;
	const int size = 5;

public:

	static Lawn* Instance() {
		static Lawn* instance = new Lawn;

		return instance;

	}

	void update(RenderWindow& window);

	virtual bool collisionLawnZombie(int* coordinatesZombie);

	string getMoverState(int i) { return mover[i]; }

	~Lawn()
	{
		delete[] mover;
		delete[] timer;
	}

	void draw(RenderWindow& window);
};

