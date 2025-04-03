#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"  
#include "Enemy.hpp"   

class Player {
public:
    Player(float startX, float startY);

    sf::Texture texture;
    sf::Sprite sprite;

    void handleInput(float deltaTime);
    void update(float deltaTime, std::vector<Enemy>& enemies); // Gegner als Parameter hinzufügen
    void draw(sf::RenderWindow& window);
	sf::Sprite GetSprite();
	//bool IsEnemyKilled();

    bool IsEnemyKilled() const;
	void ResetEnemyKillFlag();
    std::vector<Bullet>& getBullets();  

private:
    

    sf::RectangleShape shape;
    std::vector<Bullet> bullets;
    std::vector<Enemy> enemies; // Liste von Gegnern
    float speed = 300.f;
    bool canShoot = true;
    float shootCooldown = 0.3f;
    float shootTimer = 0.0f;

    bool killedEnemy = false;  

	
    //void checkCollisions(); 
};
