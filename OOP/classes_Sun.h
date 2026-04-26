#pragma once
#include<iostream>
using namespace std;

#include "SFML/Graphics.hpp"
class Sun {
private:
    //sf::Texture sunTexture;
   //if (!sunTexture.loadFromFile("assets/Plants/Sun/Sun_0.png")) {
   //    return EXIT_FAILURE ;
   //}

    float x, y;
    float stopY;
    float speed;
    sf::Time duration;
    sf:: Clock clock;
    bool active;
public:
    Sun(float startX, float startY, float stopY, float speed, sf::Time duration)
        : x(startX), y(startY), stopY(stopY), speed(speed), duration(duration), active(true) {}

    void update(sf::Time elapsedTime) {
        if (elapsedTime >= duration) {
            active = false; // If the duration has elapsed, deactivate the sunflower
        }
        else {
            y += speed; // Move the sunflower down
            if (y >= stopY) {
                y = stopY; // Stop the sunflower when it reaches the stop point
            }
        }
    }

    sf::Vector2f getPosition() const { return sf::Vector2f(x, y); }

    bool isActive() const { return active;
    }


    //// Set up sunflower sprite
    // 
    // time = timer % 220
    // time /= 10
    // imageFile = "assets/Plants/Sun/Sun_" + to_string(time) + ".png"
    // 
    //sf::Sprite sunSprite(sunTexture);
    //sunSprite.setOrigin(sunTexture.getSize().x / 2.0f, sunTexture.getSize().y / 2.0f);
    //const float startY = sunTexture.getSize().y / 2.0f; // Start sunflowers above the screen
    //const float stopY = 400.0f; // Stop point for the sunflowers
    //const float speed = 2.0f; // Speed of the sunflowers
    //const sf::Time duration = sf::seconds(5.0f); // Duration before sunflowers disappear
    //Sun sun(rand()%700+200, startY, stopY, speed, duration);
    //   sf::Time elapsedTime = clock.restart();
    //    if (sun.isActive()) {
    //        sun.update(elapsedTime);
    //        sunSprite.setPosition(sun.getPosition());
    //        window.draw(sunSprite);
    //    }

};
