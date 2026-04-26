#ifndef PEASHOOTER_H
#define PEASHOOTER_H

#include "SFML/Graphics.hpp"
//#include "classes_Zombies.h"
#include <iostream>
#include <string>

const int pixelx = 1000;
const int pixely = 600;

using namespace std;

class Pea {
public:

    string type;

    string state;
    int x, y;
    sf::Sprite peaSprite;
    int time;
    sf::Texture peaTexture;

    int damage;

    Pea()
    {
        damage = 20;
        x = 0;
        y = 0;
        time = 0;
    }
    Pea(int startX, int startY, string name) {

        damage = 20;
        state = "move";
        if (name == "peashooter") {
            type = "bullet";
            peaTexture.loadFromFile("assets/Bullets/PeaNormal/PeaNormal_0.png");
            damage = 20;
        }
        else if (name == "snowpea") {
            type = "snow";
            peaTexture.loadFromFile("assets/Bullets/PeaIce/icepea.png");
            damage = 2;
        }
        else 
            peaTexture.loadFromFile("assets/Bullets/PeaNormal/PeaNormal_0.png");
        peaSprite.setTexture(peaTexture);
        x = startX + 30;
        y = startY + 10;
        time = 0;
    }
 
    Pea(int startX, int startY, string name,int delay) {

        damage = 20;
        state = "move";
        if (name == "peashooter")
            peaTexture.loadFromFile("assets/Bullets/PeaNormal/PeaNormal_0.png");
        else if (name == "snowpea")
            peaTexture.loadFromFile("assets/Bullets/PeaIce/icepea.png");
        else
            peaTexture.loadFromFile("assets/Bullets/PeaNormal/PeaNormal_0.png");
        peaSprite.setTexture(peaTexture);
        x = startX + 30;
        y = startY + 10;
        time = -10;
    }

    void update(sf::RenderWindow& window) {
        
        //returns if pea is not drawn
        if (time < 0) {
            time++;
            return;
        }
        //checks current position of pea dependent on time
        int current = time * 10 + x;
        if (state == "move") { 

            //destroys pea if outside screen
            time++;
            if (current > pixelx - 30) {
                time = 0;
            }
            peaSprite.setPosition(current, y);
            window.draw(peaSprite);
            
        }
        //countdown to check if pea hits zombie
        else if (state == "explode") {

            static int countdown = 0;
            if (countdown > 20) {
                state = "move";
                countdown = 0;
            }
            countdown++;

        }

        CollisionZombie();

    }

    void explode() {
        state = "explode";
        time = 0;
    }

    void CollisionZombie() {

        //calls zombie instance
        ZombieFactory* zombie = ZombieFactory::Instance();

        for (int zombieCount = 0; zombieCount < zombie->getSize(); zombieCount++) {

            //checks if zombie exists
            if (zombie->list[zombieCount]->checkState() != "move" && zombie->list[zombieCount]->checkState() != "stop") {
                continue;
            }

            int zombiex = zombie->list[zombieCount]->getX();
            int zombiey = zombie->list[zombieCount]->getY();

            int zombiew = zombie->list[zombieCount]->getWidth();//width if zombie
            int zombieh = zombie->list[zombieCount]->getHeight();//height of zombie

            int peaX = time * 10 + x;

            //checks collision with zombie
            if (peaX < zombiex + zombiew && peaX > zombiex && y < zombiey + zombieh && y + 20 > zombiey) {
                
                // if peashotter than damages
                if (type == "bullet") {
                    bool died = zombie->list[zombieCount]->hitBullet(damage);
                    explode();
                }

                // if slow pea then slows down the zombie
                else {
                    bool died = zombie->list[zombieCount]->hitBullet(damage / 2);
                    explode();
                    zombie->list[zombieCount]->slowed();
                }

            }

        }
    }

};


#endif