#include "classses_Score.h"
#include <iostream>
#include "SFML/Graphics.hpp"
#include <string>
#include "classes_Cards.h"
#include<fstream>
#include<sstream>
//#include "classes_Lawn.h"
//#include "classes_Zombies.h"
//#include "classes_Plants.h"

using namespace std;
//
//void Score::loadHighScores() {
//    ifstream readfile;
//    
//    readfile.open("highscores.txt");
//    if (readfile.is_open()) {
//        numHighScores = 0;
//        while (!readfile.eof()) {
//            
//            readfile >> playerNames[numHighScores] >> readScores[numHighScores];
//                numHighScores++;
//                if (numHighScores >= MaxHighScores) {
//                    break;  // Limit reached
//                }
//                stringstream temp(readScores[numHighScores]);
//                temp >> scores[numHighScores];
//                cout << "scores" << scores[numHighScores] << endl;
//        }
//
//        readfile.close();
//
//
//    }
//
//    else {
//        cout << "Unable to open highscores.txt for reading!" << endl;
//    }
//}

void Score::loadHighScores() {
    ifstream readfile("highscores.txt");

    if (readfile.is_open()) {
        numHighScores = 0;
        while (numHighScores < MaxHighScores && readfile >> playerNames[numHighScores] >> scoresArray[numHighScores]) {
            cout << "scores " << scoresArray[numHighScores] << endl;
            numHighScores++;
        }
        readfile.close();
    }
    else {
        cout << "Unable to open highscores.txt for reading!" << endl;
    }
}


void Score::saveHighScores(string CurrName,int scores) {
    //ofstream file("highscores.txt");
    //if (file.is_open()) {
    //    cout <<  "highscores.txt for writing!" << endl;
    //    for (int i = 0; i < numHighScores; ++i) {
    //        file << playerNames[i] << " " << scores[i] << endl;
    //    }
    //    file.close();
    //}
    //else {
    //    cout << "Unable to open highscores.txt for writing!" << endl;
    //}
 if(!CurrName.empty())
    {
        ofstream scoreFile("highscores.txt");
        if (scoreFile.is_open())
        {
            if (scores > scoresArray[numHighScores]) {
                scoresArray[numHighScores] = scores;
            }
            for (int i = 0; i < numHighScores; i++) {
                scoreFile << CurrName << " "  << scoresArray[i] << endl;
            }
            scoreFile.close();
        
        }
        else
        {
            cout << "Error opening the highscores file.\n";
        }
}

}
void Score::displayHighScores(sf::RenderWindow& window) {
    // Clear the window
  //  window.clear(sf::Color::White);

    // Display high scores
    sf::Font font;
    if (!font.loadFromFile("PaytoneOne-Regular.ttf")) {
        cout << "Failed to load font!" << endl;
        return;
    }

    sf::Text title("High Scores", font, 30);
    //cout << "text" << endl;
    title.setPosition(100, 50);
    title.setFillColor(sf::Color::Black);
    float posY = 100;
    cout << "numhighscores" << numHighScores << endl;
    // Sort high scores in descending order (once)
    for (static int i = 0; i < numHighScores; ++i) {
        if (numHighScores > 1) {

            cout << "inside loop " << endl;
            for (int j = i + 1; j < numHighScores; ++j) {
                // cout << "in 2nd loop " << endl;
                if (scoresArray[j] > scoresArray[i]) {
                    int tempScore = scoresArray[i];
                    scoresArray[i] = scoresArray[j];
                    scoresArray[j] = tempScore;
                    cout << "bubble sort" << endl;
                    string tempName = playerNames[i];
                    playerNames[i] = playerNames[j];
                    playerNames[j] = tempName;
                }
                
            }

        }
        
    }

    
    for (int i = 0; i < numHighScores; i++) {
        sf::Text text(playerNames[i] + " - " + to_string(scoresArray[i]), font, 20);
        text.setPosition(100, posY);
        text.setFillColor(sf::Color::White);
        window.draw(text);
        posY += 30;
    }
  

    
   /* for (int i = 0; i < numHighScores; ++i) {
       
    }*/
    window.draw(title);
   //window.display(); // Display the rendered high scores
}

void Score::addHighScore(string& playerName, int score) {
    scoresArray[0] = 500;
    readScores[0] = 500;
    if (numHighScores < MaxHighScores) {
        playerNames[numHighScores] = playerName;
        scoresArray[numHighScores] = score;
        numHighScores++;
    }
    else {
         cout << "Max number of high scores reached!" << endl;
    }
}

void Score::updateScore(string CurrName,static int scores) {
    int currScore = 0;
    string currName;
    currName = CurrName;
    currScore = scores;

    addHighScore(CurrName, currScore);
}

