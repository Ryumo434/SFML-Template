
#include "Highscore.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>


//Funktion, um den Highscore aus einer Datei zu laden
int Highscore::loadHighScore() {
    std::ifstream file("highscore.txt");  //Öffne die Datei zum Lesen
    int highScore = 0;

    if (file.is_open()) {
        file >> highScore;  //Lese den Wert des Highscores
        file.close();
    }
    else {
        std::cout << "Fehler beim Laden des Highscores!" << std::endl;
    }

    return highScore;
}

//Funktion, um den Highscore in eine Datei zu speichern
void Highscore::saveHighScore(int highScore) {
    std::ofstream file("highscore.txt");  //Öffne die Datei zum Schreiben

    if (file.is_open()) {
        file << highScore;  //Schreibe den Highscore in die Datei
        file.close();
    }
    else {
        std::cout << "Fehler beim Speichern des Highscores!" << std::endl;
    }
}
