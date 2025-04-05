#include "Enemy.hpp"

Enemy::Enemy(float startX, float startY) {
  
    shape.setPosition(startX, startY);

    shape.setSize({ 50, 50 });
    shape.setFillColor(sf::Color::Green);
}

void Enemy::update(float deltaTime) {
    //Bewegung
    shape.move(0.f, speed * deltaTime);
}

void Enemy::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Enemy::isAlive() const {
    return health > 0;
}

sf::FloatRect Enemy::getBounds() const {
    return shape.getGlobalBounds(); //Gibt den Bounding-Box des Gegners zur�ck
}


void Enemy::hit() {
    health--;
    if (health <= 0) {
        // Gegner zerst�rt
        shape.setFillColor(sf::Color::Transparent); //Gegner unsichtbar machen
       
     
		
    }


}


