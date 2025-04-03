#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float startX, float startY);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isAlive() const;
    sf::FloatRect getBounds() const;
    void hit();  // Methode, die den Gegner bei einem Treffer verletzt

    bool hasDealtDamage() const { return hasDamagedPlayer; } //Gibt den Status zurück
    void markAsDamaged() { hasDamagedPlayer = true; } //Markiert Gegner als "Schaden gemacht"

private:
    sf::RectangleShape shape;
    int health = 1; //Einfache Gegnergesundheit
    float speed = 150.f; //Bewegungsgeschwindigkeit des Gegners
    bool hasDamagedPlayer = false; //speichert, ob der Gegner schon Schaden gemacht hat

   // float& highScore; // Referenz auf highScore




};

