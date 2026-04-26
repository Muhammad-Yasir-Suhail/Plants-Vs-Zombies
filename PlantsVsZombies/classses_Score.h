#pragma once
#ifndef CLASSSES_SCORE_H
#define CLASSSES_SCORE_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "classes_Cards.h"
#include<fstream>
#include<istream>
//#include "classes_Lawn.h"
//#include "classes_Zombies.h"
//#include "classes_Plants.h"

class Score {
public:
    static const int MaxHighScores = 100;  // Maximum number of high scores
    string readScores[MaxHighScores];
    string playerNames[MaxHighScores];  // Array to store player names
    int scoresArray[MaxHighScores];  // Array to store scores
    int numHighScores;  // Current number of high scores
public:
    Score()  {
        numHighScores = 1;
    }
    void loadHighScores();
    void saveHighScores(string CurrName, int scores);
    void displayHighScores(sf::RenderWindow& window);
    void addHighScore(string& playerName, int score);
    void updateScore(string CurrName ,int time);
    void display();
};
#endif 



