
#pragma once
#include <SFML/Graphics.hpp>

class Highscore {
public:
 
	int loadHighScore();  //Methode zum Laden des Highscores aus einer Datei
	void saveHighScore(int highScore);  //Methode zum Speichern des Highscores in eine Datei

private:
};