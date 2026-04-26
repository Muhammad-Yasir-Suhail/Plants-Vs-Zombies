#pragma once
#ifndef CLASSES_PLANTS_H
#define CLASSES_PLANTS_H
#include "SFML/Graphics.hpp"
#include <string>
#include <cstdlib>
#include <ctime>
#include"classes_Bullet.h"
#include"Sun.h"

using namespace std;
using namespace sf;

const int rows = 5;
const int columns = 9;

// Calculate the size of each cell
class Plants {
public:
    Clock clock;
    int xPosition;
    int yPosition;
    int Health;
    bool isZombie;
    int priceCost;
    bool isAvailable;
    bool isAlive;
    string imageFile;
    Texture plantTexture;
    Sprite plantSprite;
    float timer;

    Plants() : Health(100), priceCost(100), isAvailable(true), imageFile(imageFile), timer(0) {
    }

    virtual void update(RenderWindow& window, int& scores) {
        timer += .23;
        animate();
        plantSprite.setPosition(xPosition, yPosition);
        window.draw(plantSprite);
    }
    virtual void animate() = 0;

    virtual void setHealth(int newHealth) = 0;

    virtual int getPriceCost() = 0;
    ///for zomie and plant collision

    void draw(RenderWindow& window) {
        plantSprite.setPosition(xPosition, yPosition);
        window.draw(plantSprite);
    }

    void reduceHealth(int damage)
    {
        this->Health -= damage;
        if (Health < 0)
            isAlive = false;

    }
    bool isPlantAlive()
    {
        return isAlive;

    }
    ////////////////////////////////
    virtual ~Plants() {}
};
class SunFlower :public Plants
{
    float sunTimer;
    int maxSuns = 10;
    int numSuns = 0;
    Sun** sun = new Sun * [maxSuns];
public:
    SunFlower(int x, int y)
    {
        sunTimer = 0;
        numSuns = 0;
        isAlive = true;
        this->xPosition = x;
        this->yPosition = y;

        Health = 300;



        priceCost = 100;
        imageFile = "assets/Plants/SunFlower/SunFlower_0.png";



    }
    void update(RenderWindow& window, int& scores) override {
        Plants::update(window, scores);
        sunTimer += clock.restart().asSeconds();
        if (sunTimer >= 10.0f && numSuns < maxSuns) {
            sun[numSuns++] = new Sun(xPosition, yPosition);
            // cout << xPosition << "    " << yPosition << endl;
            sunTimer = 0.0f; // Reset timer
        }


        int mouseX = Mouse::getPosition(window).x;
        int mouseY = Mouse::getPosition(window).y;

        for (int i = 0; i < numSuns; ++i) {
            sun[i]->drawSunFlowerSun(window);

            // If mouse cursor is on the sun, move it to (0, 0)
            if (mouseX >= sun[i]->getX() - 10 && mouseX <= sun[i]->getX() + 20 &&
                mouseY >= sun[i]->getY() - 20 && mouseY <= sun[i]->getY() + sun[i]->getHeight() + 20) {
                sun[i]->set("moving");
                sun[i]->update(0, 0);
                scores += 25;




            }
            if (sun[i]->getX() <= 10 && sun[i]->getY() <= 20) {
                // Delete the sun if it reaches (0, 0)
                delete sun[i];
                sun[i] = sun[--numSuns];

                cout << "Delete sun " << endl;
            }
        }
    }

    void setHealth(int newHealth) override {
        Health = newHealth;
    }

    int getPriceCost() override {
        return priceCost;
    }

    virtual void animate()
    {


        int state = (int)timer % 18 * 3;
        state /= 3;

        imageFile = "assets/Plants/SunFlower/SunFlower_" + to_string(state);
        imageFile += ".png";


        plantTexture.loadFromFile(imageFile);

        plantSprite.setTexture(plantTexture);
    }

    virtual ~SunFlower()
    {

    };

};






class ShooterPlants : public Plants {
protected:
    int Damage;
    bool zombieComing;
    Pea* pea;

public:
    ShooterPlants() : Damage(0), zombieComing(false) {
        pea = nullptr;
    }

    // virtual int getDamage() = 0;
    virtual void setDamage(int newDamage) = 0;

    bool isZombiePresent(int xZ, int yZ) {
        return (xPosition < xZ && yZ == yPosition);
    }

    ~ShooterPlants()
    {
        delete pea;
    }
};



class peaShooter : public ShooterPlants {



public:
    peaShooter(int x, int y) {

        Health = 300;
        Damage = 20;
        priceCost = 100;
        imageFile = "assets/Plants/Peashooter/Peashooter_0.png";
        isAlive = true;
        xPosition = x;
        yPosition = y;

        pea = new Pea(xPosition, yPosition, "peashooter");
    }

    void setDamage(int newDamage) override {
        Damage = newDamage;
    }

    void update(sf::RenderWindow& window, int& scores) {
        Plants::update(window, scores);

        pea->update(window);

    }

    void setHealth(int newHealth) override {
        Health = newHealth;
    }

    int getPriceCost() override {
        return priceCost;
    }

    bool checkPeaCollision(int* coordinates) {
        if (pea->x + 50 > coordinates[0] && pea->x < coordinates[2] && pea->y > coordinates[1] && pea->y < coordinates[3]) {
            pea->explode();
            return true;
        }
    }

    virtual void animate()
    {


        int state = (int)timer % 13 * 5;
        state /= 5;

        imageFile = "assets/Plants/Peashooter//PeaShooter_" + to_string(state);
        imageFile += ".png";


        plantTexture.loadFromFile(imageFile);

        plantSprite.setTexture(plantTexture);
    }

    virtual ~peaShooter() {
    }

};
class repeaterPea :public ShooterPlants {
    Pea* pea2;
public:

    repeaterPea(int x, int y) {
        isAlive = true;
        Health = 300;
        Damage = 20;
        priceCost = 200;
        imageFile = "assets/Plants/RepeaterPea/RepeaterPea_0.png";

        xPosition = x;
        yPosition = y;
        pea2 = new Pea(x, y, "repeater", 1);
        pea = new Pea(x, y, "repeater");

    }

    void setDamage(int newDamage) override {
        Damage = newDamage;
    }

    void update(RenderWindow& window, int& scores) override {
        Plants::update(window, scores);

        pea->update(window);

        pea2->update(window);

    }

    void setHealth(int newHealth) override {
        Health = newHealth;
    }

    int getPriceCost() override {
        return priceCost;
    }

    virtual void animate()
    {


        int state = (int)timer % 15 * 5;
        state /= 5;

        imageFile = "assets/Plants/RepeaterPea/RepeaterPea_" + to_string(state);
        imageFile += ".png";


        plantTexture.loadFromFile(imageFile);

        plantSprite.setTexture(plantTexture);
    }

    virtual ~repeaterPea() {
        delete pea2;
    }



};
class snowPea :public ShooterPlants {

public:

    snowPea(int x, int y) {

        Health = 300;
        Damage = 20;
        priceCost = 100;
        imageFile = "assets/Plants/SnowPea/SnowPea_0.png";
        isAlive = true;
        xPosition = x;
        yPosition = y;
        pea = new Pea(x, y, "snowpea");
    }


    void setDamage(int newDamage) override {
        Damage = newDamage;
    }

    void update(sf::RenderWindow& window, int& scores) override {
        Plants::update(window, scores);
        pea->update(window);


    }



    void setHealth(int newHealth) override {
        Health = newHealth;
    }

    int getPriceCost() override {
        return priceCost;
    }
    virtual void animate()
    {


        int state = (int)timer % 15 * 5;
        state /= 5;

        imageFile = "assets/Plants/SnowPea/SnowPea_" + to_string(state);
        imageFile += ".png";


        plantTexture.loadFromFile(imageFile);

        plantSprite.setTexture(plantTexture);
    }

    virtual ~snowPea() {
        delete pea;

    }



};
///////////////////////////////////////////////////////////////BARRIER PLANT ///////////////////////////////////////////////////////////////////////WALLNUT xD//////////////
class wallNut :public Plants {



public:

    wallNut(int x, int y) {

        Health = 4000;
        priceCost = 25;
        imageFile = "assets/Plants/WallNut/WallNut/WallNut_0.png";

        xPosition = x;
        yPosition = y;
        isAlive = true;

    }



    void update(sf::RenderWindow& window, int& scores) override {
        Plants::update(window, scores);


    }



    void setHealth(int newHealth = 500) override {
        Health = newHealth;
    }

    int getPriceCost() override {
        return priceCost;
    }
    virtual void animate()
    {


        int state = (int)timer % 16 * 5;
        state /= 5;

        imageFile = "assets/Plants/WallNut/WallNut/WallNut_" + to_string(state);
        imageFile += ".png";


        plantTexture.loadFromFile(imageFile);

        plantSprite.setTexture(plantTexture);
    }

    virtual ~wallNut() {


    }




};



//////////////////Warning Danger Ahead //////////////////////////////////////////////////////Explosive Plants////////////////////////////////////

class cherryBomb :public Plants {
    bool isExploded;


public:

    cherryBomb(int x, int y) {

        Health = 40000;
        priceCost = 150;
        imageFile = "assets/Plants/CherryBomb/CherryBomb_0.png";
        isExploded = false;
        xPosition = x - 10;
        yPosition = y;
        isAlive = true;

    }



    void update(sf::RenderWindow& window, int& scores) override {
        Plants::update(window, scores);


    }
    void setState(bool s)
    {
        isExploded = s;
    }
    bool getState()
    {
        return isExploded;

    }



    void setHealth(int newHealth = 500) override {
        Health = newHealth;
    }

    int getPriceCost() override {
        return priceCost;
    }

    virtual void animate()
    {


        int state = (int)timer / 5;
        if (timer > 30) {

            //    isALive = false;
            imageFile = "assets/Plants/CherryBomb/Boom.png";
        }
        else {
            imageFile = "assets/Plants/CherryBomb/CherryBomb_" + to_string(state);
            imageFile += ".png";

        }


        plantTexture.loadFromFile(imageFile);

        plantSprite.setTexture(plantTexture);
    }

    virtual ~cherryBomb() {


    }




};

class PlantFactory {
public:
    PlantFactory()
    {
        plants = new Plants * *[rows];
        for (int i = 0; i < rows; i++) {
            plants[i] = new Plants * [columns];
            for (int j = 0; j < columns; j++) {
                plants[i][j] = nullptr;
            }
        }
        size = 0;
    }

protected:
    Plants*** plants; // makes 2D array of Plants
    int size;

public:

    static PlantFactory* Instance() {
        static PlantFactory* instance = new PlantFactory;

        return instance;
    }

    void update(RenderWindow& window, int& scores) {
        bool plantsExist = false;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (plants[i][j] != nullptr) {
                    plantsExist = true;

                    plants[i][j]->update(window, scores);  // was checking if it is sunflower or not



                    if (!plants[i][j]->isPlantAlive()) {
                        delete plants[i][j];
                        plants[i][j] = nullptr;
                    }
                }

            }
        }
    }

    void draw(RenderWindow& window) {

        bool plantsExist = false;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {

                if (plants[i][j] != nullptr) {
                    plantsExist = true;

                    plants[i][j]->draw(window);  // was checking if it is sunflower or not


                    if (!plants[i][j]->isPlantAlive()) {
                        delete plants[i][j];
                        plants[i][j] = nullptr;
                    }
                }

            }
        }
    }

public:

    virtual   void createPlant(string plantName, int x, int y) {

        if (size < rows * columns) {

            int mouseRow = (y - 80) / 100;
            int mouseColumn = (x - 250) / 80;
            if (plants[mouseRow][mouseColumn] == nullptr) {

                int xPosition = mouseColumn * 80 + 250;
                int yPosition = mouseRow * 100 + 80;

                Plants* newPlant = nullptr;
                if (plantName == "peashooter") {
                    newPlant = new peaShooter(xPosition, yPosition);
                }
                else if (plantName == "sunflower")
                {
                    newPlant = new SunFlower(xPosition, yPosition);
                }
                else if (plantName == "repeaterpea") {
                    newPlant = new repeaterPea(xPosition, yPosition);
                }

                else if (plantName == "snowpea") {
                    newPlant = new snowPea(xPosition, yPosition);
                }
                else if (plantName == "wallnut") {
                    newPlant = new wallNut(xPosition, yPosition);
                }
                else if (plantName == "cherrybomb") {
                    newPlant = new cherryBomb(xPosition, yPosition);
                }
                /* else if (plantName == "shovel")
                 {
                     if (plants[xPosition][yPosition] != nullptr)
                         delete plants[xPosition][yPosition];


                 }*/
                plants[mouseRow][mouseColumn] = newPlant;
                size++;

            }

        }
    }

    friend void ZombieFactory::checkCollisionPlant();

    ~PlantFactory()
    {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (plants[i][j] != nullptr) {
                    delete plants[i][j];
                }
            }
            delete[] plants[i];
        }
        delete[] plants;
    }
};


#endif;