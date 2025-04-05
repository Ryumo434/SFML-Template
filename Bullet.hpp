#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float startX, float startY);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isOffScreen() const;
    sf::FloatRect getBounds() const;
    void setAlive(bool aliveStatus);  //Wird verwendet, um das Projektil als tot zu markieren
    bool isAlive() const; //prüft Aktivität des Projektils

private:
    sf::RectangleShape shape;
    float speed = 400.f; //Geschwindigkeit des Projektils
    bool alive = true; //Variable für das Leben des Projektils
};
