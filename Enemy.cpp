#include "Enemy.hpp"

Enemy::Enemy(float startX, float startY) {
    // Zuf�llige X-Position im Bereich 0 bis 800
    //float randomX = rand() % 800;

    shape.setPosition(startX, startY);

    // Zuf�llige Y-Position im Bereich 0 bis 600
   //float randomY = rand() % 600;

    // Setzt die zuf�llige Position
    //shape.setPosition(randomX, randomY);
    //shape.setPosition(randomX, 0);

    // Optional: Gegner visuell darstellen
    shape.setSize({ 50, 50 }); // Gr��e des Gegners
    shape.setFillColor(sf::Color::Green); // Farbe des Gegners
}

void Enemy::update(float deltaTime) {
    // Einfache Bewegung nach unten (kann sp�ter erweitert werden)
    shape.move(0.f, speed * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Enemy::isAlive() const {
    return health > 0;
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds(); // Gibt den Bounding-Box des Gegners zur�ck
}


void Enemy::hit() {
    health--;
    if (health <= 0) {
        // Gegner zerst�rt (kann hier eine Explosion oder ein anderes Event ausl�sen)
        shape.setFillColor(sf::Color::Transparent); // Gegner unsichtbar machen
       
        //health = 0; 
       // highScore += 10;  // Highscore erh�hen, wenn der Gegner besiegt wurde
       // std::cout << "Enemy defeated, increasing highscore." << std::endl;
        
		
    }


}


