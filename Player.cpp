#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"   
#include <iostream>

Player::Player(float startX, float startY) {
    if (!texture.loadFromFile("Assets/Sprites/MainShip.png")) {
        std::cerr << "Fehler beim Laden der Raumschiff-Textur!" << std::endl;
    }
    sprite.setTexture(texture);
    sprite.setPosition(startX, startY);
    sprite.setScale(2.f, 2.f);
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        movement.y -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        movement.y += speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        movement.x -= speed;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        movement.x += speed;

    sprite.move(movement * deltaTime);

    // Beispiel für Rotation basierend auf horizontaler Bewegung:
    if (movement.x < 0)
        sprite.setRotation(-10);
    else if (movement.x > 0)
        sprite.setRotation(10);
    else
        sprite.setRotation(0);

    // Schießen mit der Leertaste (nur einmal pro Tastendruck)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && canShoot) {
        // Nutze getGlobalBounds() um die Breite zu ermitteln
        float shipWidth = sprite.getGlobalBounds().width;
        bullets.push_back(Bullet(sprite.getPosition().x + shipWidth / 2 - 5, sprite.getPosition().y));
        canShoot = false; // Schießen verhindern, bis der Cooldown abgelaufen ist
        shootTimer = shootCooldown; // Cooldown starten
    }
}

void Player::update(float deltaTime, std::vector<Enemy>& enemies) {
    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
        // Kollisionsprüfung zwischen Projektile und Gegner
        for (auto& enemy : enemies) {
            if (bullet.getBounds().intersects(enemy.getBounds())) {
                killedEnemy = true;
                bullet.setAlive(false);
                enemy.hit();
            }
        }
    }

    // Entferne inaktive Projektile
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](Bullet& b) {
        return !b.isAlive();
        }), bullets.end());

    if (!canShoot) {
        shootTimer -= deltaTime;
        if (shootTimer <= 0.0f) {
            canShoot = true;
        }
    }

    // Update und Entfernen der Gegner
    for (auto& enemy : enemies) {
        enemy.update(deltaTime);
    }
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](Enemy& e) {
        return !e.isAlive();
        }), enemies.end());

    // Begrenzung des Spielfelds (mit Verwendung von getGlobalBounds)
    sf::Vector2f pos = sprite.getPosition();
    sf::FloatRect bounds = sprite.getGlobalBounds();
    if (pos.x < 0) pos.x = 0;
    if (pos.y < 0) pos.y = 0;
    if (pos.x > 1200 - bounds.width) pos.x = 1200 - bounds.width;
    if (pos.y > 760 - bounds.height) pos.y = 760 - bounds.height;
    sprite.setPosition(pos);
}

std::vector<Bullet>& Player::getBullets() {
    return bullets;
}

void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
    for (auto& bullet : bullets) {
        bullet.draw(window);
    }
}

bool Player::IsEnemyKilled() const {
    return killedEnemy;
}

void Player::ResetEnemyKillFlag() {
    killedEnemy = false;
}

sf::Sprite Player::GetSprite() {
    return sprite;
}
