#pragma once
#include <iostream>
#include "SFML/Graphics.hpp"
#include "Header.h"
#include <string>
#include "classes_Levels.h"
#include "classes_instruction.h"
#include "classses_Score.h"
#include <cmath>
#include "Sun.h"

//stores programs

using namespace std;
using namespace sf;

void startScreen(RenderWindow& window) {

	//executes and deals with the start screen layout etc

	Sprite backgroundSpriteStart;
	Texture texture;

	Sprite button;
	Texture textureButton;
	

	texture.loadFromFile("assets/Background/start1.png");
	backgroundSpriteStart.setTexture(texture);

	float scaleX = pixelx / static_cast<float>(texture.getSize().x);
	float scaleY = pixely / static_cast<float>(texture.getSize().y);

	// Scale the sprite
	backgroundSpriteStart.setScale(scaleX, scaleY);
	backgroundSpriteStart.setPosition(0, 0);
	
	window.draw(backgroundSpriteStart);

	textureButton.loadFromFile("assets/Background/PlayButton.png");

	button.setTexture(textureButton);
	button.setPosition(80, 500);

	window.draw(button);

	textureButton.loadFromFile("assets/Background/instructions.png");

	button.setTexture(textureButton);
	button.setPosition(380, 500);

	window.draw(button);

	textureButton.loadFromFile("assets/Background/score.png");

	button.setTexture(textureButton);
	button.setPosition(680, 500);

	window.draw(button);

}

void spriteStart(RenderWindow& window) {
	Texture texture;
	Sprite sprite;
	static int count;
	int x = 0;

	x = pow((count++)*1.8 - 80,3) / 790 + 460 + count;

	texture.loadFromFile("assets/Inventory-GameScreen/StartButton.png");

	sprite.setScale(1.5f, 1.5f);

	sprite.setTexture(texture);
	sprite.setPosition(x, 280);

	window.draw(sprite);

}

int sun(RenderWindow& window) {

	Clock clock;
	static int scores = 100;
	const int maxSuns = 5;
	int numSuns = 0;
	Sun* suns[maxSuns];
	float nextSunTime = 0.0f;
	const float SUN_INTERVAL_MIN = 1.0f;
	const float SUN_INTERVAL_MAX = 5.0f;
	float initialDelay = 3.0f;
	float elapsedInitialDelay = 0.0f;

	if (Mouse::isButtonPressed && Mouse::Button() == Mouse::Left) {

		for (int i = 0; i < numSuns; ++i) {
			int mouseX = Mouse::getPosition(window).x;
			int mouseY = Mouse::getPosition(window).y;
			if (mouseX >= suns[i]->getX() - 20 && mouseX <= suns[i]->getX() + suns[i]->getWidth() &&
				mouseY >= suns[i]->getY() - 20 && mouseY <= suns[i]->getY() + suns[i]->getHeight() + 20) {
				suns[i]->set("moving");
				
				suns[i]->update(0, 0);
				scores += 50;

			}
		}
	}
	elapsedInitialDelay += clock.restart().asSeconds();

	float deltaTime = clock.restart().asSeconds();
	nextSunTime -= deltaTime;
	if (nextSunTime <= 0 && numSuns < maxSuns) {

		int xPos = rand() % 800; // Random x position
		int yPos = 0; // Start at the top of the screen
		suns[numSuns++] = new Sun(xPos, yPos);
		nextSunTime = SUN_INTERVAL_MIN + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (SUN_INTERVAL_MAX - SUN_INTERVAL_MIN)));
	}

	// Update and draw suns
	for (int i = 0; i < numSuns; ++i) {
		suns[i]->update(0, 0);
		suns[i]->drawSun(window);
		if (suns[i]->getX() < 10 && suns[i]->getY() <= 10) {
			scores += 50;
			//cout << scores << endl;
			delete suns[i]; // Free memory
			suns[i] = suns[--numSuns];
		}

		if (suns[i]->getY() >= 400) { // Adjust y position as needed
			delete suns[i]; // Free memory
			suns[i] = suns[--numSuns];
		}
	}

	return scores;

}

void gameScreen(RenderWindow& window, Level** level, Clock& clock,int &scores) {

//	int score = sun(window);

	static int levelIndex = 0;

	//setting background
	Sprite top;
	Texture topT;
	Sprite backgroundSpriteStart;
	Texture texture;

	texture.loadFromFile("assets/Background/bgday.jpg");
	backgroundSpriteStart.setTexture(texture);
	int x = 0;
	if (clock.getElapsedTime().asSeconds() < 5) {
		x =clock.getElapsedTime().asMilliseconds()* 0.08 -400;
		backgroundSpriteStart.setPosition(x, 0);
	}
	else
		backgroundSpriteStart.setPosition(x, 0);

	window.draw(backgroundSpriteStart);

	topT.loadFromFile("assets/Inventory-GameScreen/ChooserBackground.png");
	top.setTexture(topT);
	top.setPosition(0, 0);

	window.draw(top);

	if (clock.getElapsedTime().asSeconds() < 5) {
		spriteStart(window);
	}
	level[levelIndex]->update(window, scores);

	if (level[levelIndex]->endLevel() == true) {
		delete level[levelIndex];
		levelIndex + 1;
	}

	

}

void pauseScreen(RenderWindow& window, Level** level, Clock& clock, int& scores) {

	Sprite top;
	Texture topT;

	int i = 0;

	if (level[i] == nullptr) {
		i++;
		if (level[i] == nullptr) {
			i++;
			if (level[i] == nullptr) {
				i++;
			}
		}
	}

	//setting background
	Sprite backgroundSpriteStart;
	Texture texture;


	
	//background sprite
	texture.loadFromFile("assets/Background/bgday.jpg");
	backgroundSpriteStart.setTexture(texture);
	
	//pause button sprite
	Sprite pause;
	Texture pTexture;
	pTexture.loadFromFile("assets/Background/play.png");
	pause.setTexture(pTexture);
	pause.setPosition(pixelx/2, pixely/2);

	topT.loadFromFile("assets/Inventory-GameScreen/ChooserBackground.png");
	top.setTexture(topT);
	top.setPosition(0, 0);
	
	//draw all sprites
	window.draw(backgroundSpriteStart);
	window.draw(top);
	window.draw(pause);

	level[i]->pause(window);

}

bool instructScreen(RenderWindow& window, Event& event, inst& ins) {

	return ins.update(window, event);

}

void NameScreen(RenderWindow& window) {					//high score

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/Background/HighScoreScreenBackground.png")) {
		std::cout << "Failed to load background image!" << std::endl;
		return;
	}

	// Create a sprite for the background and set its texture
	sf::Sprite backgroundSprite(backgroundTexture);


	// Adjust scaling factors based on image and window dimensions
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(scaleX, scaleY);

	// Draw the background sprite first
	window.draw(backgroundSprite);



	// Display everything on the window

	//background sprite
	//texture.loadFromFile("assets/Background/HighScoreScreenBackground.png");
	//backgroundSprite.setTexture(texture);


	//draw all sprites
	window.draw(backgroundSprite);


}

void scoreScreen(RenderWindow& window) {
	Score Scoreboard;

	sf::Texture backgroundTexture;
	if (!backgroundTexture.loadFromFile("assets/Background/HighScoreScreenBackground.png")) {
		cout << "Failed to load background image!" << endl;
		return;
	}

	// Create a sprite for the background and set its texture
	sf::Sprite backgroundSprite(backgroundTexture);


	// Adjust scaling factors based on image and window dimensions
	float scaleX = static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x;
	float scaleY = static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y;
	backgroundSprite.setScale(scaleX, scaleY);

	// Draw the background sprite first
	window.draw(backgroundSprite);

	// Display everything on the window
	//window.display();
	static int check = 0;
	if (check == 0) {
		Scoreboard.loadHighScores();
		check = 1;
	}

	Scoreboard.displayHighScores(window); // Then display the high scores
	//Scoreboard.updateScore(currName)



}