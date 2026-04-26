#include <iostream>
#include "SFML/Graphics.hpp"
#include "Header.h"
#include "classes_Player.h"
#include <string>
#include <cstdlib>
#include <ctime>
#include"Sun.h"

using namespace std;
using namespace sf;

int main() {
   static int scores = 100;
    Font scoreFont;
    scoreFont.loadFromFile("assets/fonts/SamdanEvil.ttf");
    Text score;
    score.setFont(scoreFont);
    score.setPosition(23, 60);
    score.setCharacterSize(18);
    score.setString(to_string(scores));

    //scores related declarations
    bool nameEntered = false;
    string CurrName;
    Font font;
    if (!font.loadFromFile("PaytoneOne-Regular.ttf")) {
        // Error handling for font loading failure
        cout << "Error while loading font " << endl;
    }
    Text playerNameText;
    playerNameText.setFont(font);
    playerNameText.setCharacterSize(24);
    playerNameText.setString("Enter your name");
    playerNameText.setFillColor(Color::White);
    playerNameText.setPosition(10, 10); // Adjust position as needed


    // sun related declaration
   const int maxSuns=5;
    int numSuns=0;
    Sun* suns[maxSuns];
    float nextSunTime = 0.0f;
    const float SUN_INTERVAL_MIN = 1.0f; 
    const float SUN_INTERVAL_MAX = 5.0f;
    float initialDelay = 3.0f;
    float elapsedInitialDelay = 0.0f;
    srand(time(0));
	String currWindows = "start";

	RenderWindow window(VideoMode(pixelx, pixely), "SFML Window Close Example");
    Clock clock;
    Clock clock2;
  //  window.setFramerateLimit(80);
    //declaring all required variables

    Level** level;

    level = new Level*[4];
    level[0] = Level1::Instance();
    level[1] = Level2::Instance();
    level[2] = Level3::Instance();
    level[3] = Level4::Instance();

	Player& player = Player::getInstance();

    inst ins;
  
    
	srand(time(0));
    while (window.isOpen()) { // Check if the window is still open
        Event event;

        // Event polling loop
        while (window.pollEvent(event)) {
            // If the user closes the window
            if (event.type == Event::Closed) {
                window.close(); // Close the window
            }

            else if (event.type == Event::TextEntered && !nameEntered) {
                if (event.text.unicode < 128) {
                    if (event.text.unicode == 13) {
                        // Enter key pressed, name entered
                        nameEntered = true;
                        currWindows = "start";
                    }
                    else if (event.text.unicode == 8 && !CurrName.empty()) {
                        // Backspace pressed, remove last character from name
                        CurrName.pop_back();
                    }
                    else if (CurrName.size() < 100 && event.text.unicode != 8) { // Limit input length and ignore backspace
                        CurrName += static_cast<char>(event.text.unicode);
                    }
                    playerNameText.setString("Enter your name:     " + CurrName);
                }
            }

            // You can handle other events here, like key presses, mouse movements, etc.
        }

        // Clear the window
        window.clear(Color::Black);
        
        // call all functions to perform actions
        if (currWindows == "start") {
            startScreen(window);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                currWindows = "game";
                clock.restart();
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
                currWindows = "instructions";
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
                currWindows = "Scores";

            
           
            if (Mouse::isButtonPressed&&event.mouseButton.button == Mouse::Left ) {
                if (Mouse::getPosition(window).x > 80 && Mouse::getPosition(window).x < 320 && Mouse::getPosition(window).y > 500 && Mouse::getPosition(window).y < 600) {
                    if (Mouse::isButtonPressed)
                    currWindows = "game";
                    clock.restart();
                    //creates class instances for level, players, zombies etc
                }
                else if (Mouse::getPosition(window).x > 380 && Mouse::getPosition(window).x < 620 && Mouse::getPosition(window).y > 500 && Mouse::getPosition(window).y < 600)
                    currWindows = "instructions";
                else if (Mouse::getPosition(window).x > 680 && Mouse::getPosition(window).x < 920 && Mouse::getPosition(window).y > 500 && Mouse::getPosition(window).y < 600)
                    currWindows = "Scores";
            }
            
        }



        else if (currWindows == "game") {
            gameScreen(window, level, clock,scores);
            
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                currWindows = "pause";
            }

            string win = level[3]->checkWin();
            cout << win;

            if (level[0] == nullptr && level[1] == nullptr && level[2] == nullptr) {

                if (win == "lost") {
                    currWindows = "lost";
                }
                else if (win == "win") {
                    currWindows = "win";
                }

            }
        }

        else if (currWindows == "win") {
            
            Texture bgt;
            Sprite bg;

            bgt.loadFromFile("assets/Background/end.png");
            bg.setTexture(bgt);
            bg.setPosition(0, 0);
            window.draw(bg);

            bgt.loadFromFile("assets/Inventory-GameScreen/win.png");
            bg.setTexture(bgt);
            bg.setPosition(112, 25);
            window.draw(bg);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                currWindows = "start";
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    currWindows = "start";
                }
            }
        }

        else if (currWindows == "lost") {

            Texture bgt;
            Sprite bg;

            bgt.loadFromFile("assets/Background/end.png");
            bg.setTexture(bgt);
            bg.setPosition(0, 0);
            window.draw(bg);

            bgt.loadFromFile("assets/Inventory-GameScreen/lost.png");
            bg.setTexture(bgt);
            bg.setPosition(118, 0);
            window.draw(bg);

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
                currWindows = "start";
            }

            if (event.type == Event::MouseButtonPressed) {
                if (event.mouseButton.button == Mouse::Left) {
                    currWindows = "start";
                }
            }
        }
        else if(currWindows == "pause"){
        	pauseScreen(window, level, clock, scores);
        	
        	if(event.type == Event::MouseButtonPressed){
            	if (event.mouseButton.button == Mouse::Left){
            		currWindows = "game";
            	}
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
                currWindows = "game";
            }
        }
        else if(currWindows == "instructions") {
            if (instructScreen(window, event, ins))
                currWindows = "start";
        }

        else if (currWindows == "name") {
            NameScreen(window);
            Text Name;
            Name.setFont(font);
            Name.setCharacterSize(24);
            Name.setFillColor(Color::White);
            Name.setPosition(30, 50); // Adjust position as needed
            window.draw(playerNameText);
            window.draw(Name);
        }
        else if (currWindows == "Scores") {
            scoreScreen(window);
            //   Scoreboard.saveHighScores(CurrName);
            Score Scoreboard;
            Scoreboard.saveHighScores(CurrName, scores);
            }

        if (Mouse::isButtonPressed && event.mouseButton.button == Mouse::Left) {

            for (int i = 0; i < numSuns; ++i) {
                int mouseX = Mouse::getPosition(window).x;
                int mouseY = Mouse::getPosition(window).y;
                if (mouseX >= suns[i]->getX()-10 && mouseX <= suns[i]->getX() + suns[i]->getWidth() &&
                    mouseY >= suns[i]->getY() - 20 && mouseY <= suns[i]->getY() + suns[i]->getHeight() + 20) {
                    suns[i]->set("moving");

                    suns[i]->update(0, 0);
                    //    scores += 50;

                }
            }
        }
        float deltaTime = clock2.restart().asSeconds();
        nextSunTime -= deltaTime;
        if (nextSunTime <= 0 && numSuns < maxSuns){
            int xPos = rand() % 800; 
            int yPos = 0; 
            suns[numSuns++] = new Sun(xPos); 
            nextSunTime = SUN_INTERVAL_MIN + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (SUN_INTERVAL_MAX - SUN_INTERVAL_MIN)));
        }

        // Update and draw suns
        for (int i = 0; i < numSuns; ++i) {
            suns[i]->update(0, 0);
            suns[i]->drawSun(window);
            if (suns[i]->getY() >= 400) { // Adjust y position as needed
                delete suns[i]; // Free memory
                suns[i] = suns[--numSuns];
            }
            else   if (suns[i]->getX() < 10 && suns[i]->getY() <= 10) {
                scores += 25;
                delete suns[i]; // Free memory
                suns[i] = suns[--numSuns];
            }
        }



        score.setString(to_string(scores));

        window.draw(score);
        window.display();

    }

    return 0;
}
