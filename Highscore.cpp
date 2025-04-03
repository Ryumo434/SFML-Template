// Highscore.cpp
#include "Highscore.hpp"
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>

/*
Highscore::Highscore() : score(0) {
    if (!font.loadFromFile("Assets/Fonts/ARIAL.TTF")) {
        // Fehlerbehandlung, falls die Schriftart nicht geladen werden kann
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(50.f, 50.f);  // Position des Scores auf dem Bildschirm
}

void Highscore::increment() {
    score++;  // Erhöht den Score
}

void Highscore::draw(sf::RenderWindow& window) {
    scoreText.setString("Highscore: " + std::to_string(score));  // Setzt den Text des Scores
    window.draw(scoreText);  // Zeichnet den Score auf das Fenster
}*/



// Funktion, um den Highscore aus einer Datei zu laden
int Highscore::loadHighScore() {
    std::ifstream file("highscore.txt");  // Öffne die Datei zum Lesen
    int highScore = 0;

    if (file.is_open()) {
        file >> highScore;  // Lese den Wert des Highscores
        file.close();
    }
    else {
        std::cout << "Fehler beim Laden des Highscores!" << std::endl;
    }

    return highScore;
}

// Funktion, um den Highscore in eine Datei zu speichern
void Highscore::saveHighScore(int highScore) {
    std::ofstream file("highscore.txt");  // Öffne die Datei zum Schreiben

    if (file.is_open()) {
        file << highScore;  // Schreibe den Highscore in die Datei
        file.close();
    }
    else {
        std::cout << "Fehler beim Speichern des Highscores!" << std::endl;
    }
}
