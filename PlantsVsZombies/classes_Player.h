#ifndef CLASSES_PLAYER_H
#define CLASSES_PLAYER_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>

//stores player class 

using namespace std;
using namespace sf;

class Player{
	
	int sun;
	int health;
	
	Player(){
	}
	
public:

	static Player& getInstance(){
		static Player instance;
		return instance;
	}
	
	Player (const Player&) = delete;
	
	Player& operator = (const Player&) = delete;
	
	
};

#endif