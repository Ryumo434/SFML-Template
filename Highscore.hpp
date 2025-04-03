// Highscore.hpp
#pragma once
#include <SFML/Graphics.hpp>

class Highscore {
public:
    //Highscore();

    //void increment();  // Methode zum Erhöhen des Highscores
   // void draw(sf::RenderWindow& window);  // Methode zum Zeichnen des Highscores
	int loadHighScore();  // Methode zum Laden des Highscores aus einer Datei
	void saveHighScore(int highScore);  // Methode zum Speichern des Highscores in eine Datei

private:
    //int score;  // Der Highscore
    //sf::Text scoreText;  // Textobjekt, um den Score darzustellen
    //sf::Font font;  // Die Schriftart für den Score
};