#include "Bullet.hpp"

Bullet::Bullet(float startX, float startY) {
    shape.setSize({ 10, 30 }); // Größe des Projektils
    shape.setFillColor(sf::Color::Red);
    shape.setPosition(startX, startY);
}

void Bullet::update(float deltaTime) {
    // Bewege das Projektil nach oben
    shape.move(0.f, -speed * deltaTime);

    // Wenn das Projektil aus dem Bildschirm verschwindet, setze es als tot
    if (shape.getPosition().y < 0) {
        alive = false;
    }
}

void Bullet::draw(sf::RenderWindow& window) {
    if (alive) {
        window.draw(shape);
    }
}

sf::FloatRect Bullet::getBounds() const {
    return shape.getGlobalBounds();
}

void Bullet::setAlive(bool aliveStatus) {
    alive = aliveStatus;
}

bool Bullet::isAlive() const {
    return alive;
}
