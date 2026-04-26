#pragma once
#include<iostream>
using namespace std;
using namespace sf;
#include<cmath>
#include "SFML/Graphics.hpp"
#include <SFML/Window/Event.hpp>
class Sun {
private:
    // int scores;
    Texture sunTexture;
    string isSunPresent;
    Sprite sunSprite;

    float x, currentY;
    float stopY;
    float speed;
    float timer;
    string imageFile;;

  
public:
    //  Event event;
    Sun(int xp)
    {
        currentY = 0;
        x = xp;
       // currentY = yp;
       ;
        imageFile = "assets/Plants/Sun/Sun_0.png";
        sunTexture.loadFromFile(imageFile);
        sunSprite.setTexture(sunTexture);
        stopY = 460.0f;
        speed = 2.0;
        timer = 0;
        isSunPresent = "falling";
    }

    Sun(int stX, int stY)
    {
        x = stX;
        currentY = stY;

        isSunPresent = "present";
        imageFile = "assets/Plants/Sun/Sun_0.png";
        sunTexture.loadFromFile(imageFile);
        sunSprite.setTexture(sunTexture);
        sunSprite.setPosition(stX, stY);
    }

    void update(int targetX, int targetY) {

        if (isSunPresent=="falling")
        {
            currentY += speed;

            if (currentY >= stopY)
                isSunPresent = "stop";
        }



        else if(isSunPresent=="moving") {
            float dirX = targetX - x;
            float dirY = targetY - currentY;
            float distanceToTarget = sqrt(dirX * dirX + dirY * dirY);
            if (distanceToTarget == 0) {
                return;
            }
            if (distanceToTarget > 0)
            {
                dirX /= distanceToTarget;
                dirY /= distanceToTarget;

                x += dirX * ((speed * 4.0f) + 2.0f);
                currentY += dirY * ((speed * 2) + 3.0f);

            }
        }
    }
    void drawSun(RenderWindow& window)
    {
        timer += .23;
        animate();
        sunSprite.setPosition(x, currentY);
        window.draw(sunSprite);

    }
    void drawSunFlowerSun(RenderWindow& window)
    {
        timer += .23;
        animate();
        sunSprite.setPosition(x+20, currentY-30);
        sunSprite.setScale(0.7, 0.7);
        window.draw(sunSprite);

    }
    void setX(int X)
    {
        this->x = X;

    }
    void setY(int Y)
    {
        this->currentY = Y;

    }
    float getX()
    {
        return this->x;

    }

    float getY()
    {
        return this->currentY;

    }
    void set(string set)
    {

        isSunPresent = set;
    }
    void animate()
    {


        int state = (int)timer % 21 * 3;
        state /= 3;

        imageFile = "assets/Plants/Sun/Sun_" + to_string(state);
        imageFile += ".png";


        sunTexture.loadFromFile(imageFile);

        sunSprite.setTexture(sunTexture);
    }


    /*bool isActive() const {
        return isSunFalling;
    }*/

    int getWidth()
    {
        return 20;
    }
    int getHeight()
    {
        return 20;
    }
};
