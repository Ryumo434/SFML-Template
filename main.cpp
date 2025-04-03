#include "main.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>  // Fügt std::cout hinzu
#include <fstream>
#include <filesystem>
#include "..//Player.hpp"
#include "..//Enemy.hpp"
#include "..//Highscore.hpp"
#include <ctime>  // Für std::time              
#include <vector>
#include <cstdlib> // Für std::rand()
#include <algorithm> // Für std::shuffle
#include <random>    // Für std::default_random_engine

enum GameState { MAIN_MENU, IN_GAME, GAME_OVER };

int main() {

    Highscore highscoreObj;
    int highScore = highscoreObj.loadHighScore(); // Initialer Highscore
    int playerScore = 0; // Spieler-Score

    // Initialisiere den Zufallszahlengenerator
    std::srand(std::time(0));

    sf::RenderWindow window(sf::VideoMode(1200, 900), "Space Shooter");
    window.setFramerateLimit(60);

    // Laden der Schriftart   
    sf::Font font;
    if (!font.loadFromFile("Assets/Fonts/ARIAL.TTF")) {
        std::cerr << "Fehler beim Laden der Schriftart! Überprüfe den Pfad zur Datei." << std::endl;
        std::cerr << "Aktueller Arbeitsordner: " << std::filesystem::current_path() << std::endl;
    }

    // Menütitel
    sf::Text menuTitle;
    menuTitle.setFont(font);
    menuTitle.setString("Space Shooter");
    menuTitle.setCharacterSize(80);
    menuTitle.setFillColor(sf::Color::White);
    menuTitle.setPosition(340.f, 200.f);

    sf::Text menuControls;
    menuControls.setFont(font);
    menuControls.setString("(Enter) Starten\n(Esc) Beenden");
    menuControls.setCharacterSize(40);
    menuControls.setFillColor(sf::Color::White);
    menuControls.setPosition(460.f, 500.f);

    // Spielstatus
    GameState gameState = MAIN_MENU;

    // Erstelle das untere Interface-Fenster (HUD)
    sf::RectangleShape hud(sf::Vector2f(1200.f, 200.f)); // Breite = Fensterbreite, Höhe = 300px
    hud.setFillColor(sf::Color::Black);
    hud.setOutlineThickness(5.f);
    hud.setOutlineColor(sf::Color::White);
    hud.setPosition(0.f, 750.f);

    // Erstelle den Spieler
    Player player(375, 500); // Spielerposition

    // Lebensbalken
    sf::RectangleShape healthBarBg(sf::Vector2f(300.f, 25.f));
    healthBarBg.setFillColor(sf::Color::Red);
    healthBarBg.setOutlineThickness(2.f);
    healthBarBg.setOutlineColor(sf::Color::White);
    healthBarBg.setPosition(50.f, 850.f);

    sf::RectangleShape healthBar(sf::Vector2f(300.f, 25.f));
    healthBar.setFillColor(sf::Color::Green);
    healthBar.setPosition(50.f, 850.f);

    float playerHealth = 100.f;
    float maxHealth = 100.f;

    // Text über dem Lebensbalken
    sf::Text motherShipText;
    motherShipText.setFont(font);
    motherShipText.setString("Mutterschiff");
    motherShipText.setCharacterSize(24);
    motherShipText.setFillColor(sf::Color::White);
    motherShipText.setPosition(50.f, 820.f);

    // Variablen für Game Over Bildschirm
    sf::Text gameOverText;
    gameOverText.setFont(font);
    gameOverText.setString("     GAME OVER\nMutterschiff zerstört!\n\n(R)      Neustart.\n(ESC) Spiel verlassen.");
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(400.f, 300.f);

    // Liste mit festen Positionen, an denen Gegner erscheinen können
    std::vector<sf::Vector2f> spawnPositions = {
        {200.f, 0.f}, {300.f, 0.f}, {400.f, 0.f}, {500.f, 0.f},
        {600.f, 0.f}, {700.f, 0.f}, {800.f, 0.f}, {900.f, 0.f}
    };

    // Liste für Gegner
    std::vector<Enemy> enemies;

    sf::Clock clock; // Zum Messen der Zeit
    float spawnTimer = 0.0f;
    const float spawnInterval = 5.0f;

    // --- Hintergrund (Sterne) ---
    sf::Texture bgTexture;
    if (!bgTexture.loadFromFile("Assets/Sprites/spaceBackground.jpg")) {
        std::cerr << "Fehler beim Laden des Hintergrundbildes!" << std::endl;
    }
    // Zwei Sprites für den endlos scrollenden Hintergrund
    sf::Sprite bgSprite1(bgTexture);
    sf::Sprite bgSprite2(bgTexture);
    bgSprite1.setPosition(0.f, 0.f);
    bgSprite2.setPosition(0.f, -static_cast<float>(bgTexture.getSize().y));
    // Geschwindigkeit des Scrollings (Pixel pro Sekunde)
    float bgScrollSpeed = 80.f;

    // Hauptspiel-Schleife
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (gameState == MAIN_MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Enter) {
                        gameState = IN_GAME; // Spiel starten
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }
            }
            else if (gameState == GAME_OVER) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::R) {
                        // Setze das Spiel zurück
                        playerScore = 0;
                        playerHealth = 100.f;
                        healthBar.setSize(sf::Vector2f(300.f, 25.f));
                        enemies.clear();
                        spawnTimer = 0.0f;
                        clock.restart();
                        gameState = IN_GAME;
                    }
                    else if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                }
            }
        }

        // Berechne DeltaTime
        float deltaTime = clock.restart().asSeconds();

        // Hintergrund aktualisieren (nur im Spielmodus)
        if (gameState == IN_GAME) {
            bgSprite1.move(0.f, bgScrollSpeed * deltaTime);
            bgSprite2.move(0.f, bgScrollSpeed * deltaTime);

            // Wenn ein Sprite aus dem Fenster läuft, setze es wieder oben an
            if (bgSprite1.getPosition().y >= static_cast<float>(bgTexture.getSize().y))
                bgSprite1.setPosition(0.f, bgSprite2.getPosition().y - static_cast<float>(bgTexture.getSize().y));
            if (bgSprite2.getPosition().y >= static_cast<float>(bgTexture.getSize().y))
                bgSprite2.setPosition(0.f, bgSprite1.getPosition().y - static_cast<float>(bgTexture.getSize().y));
        }

        // Spielzustände zeichnen
        window.clear();

        if (gameState == MAIN_MENU) {
            window.draw(menuTitle);
            window.draw(menuControls);
        }
        else if (gameState == IN_GAME) {
            // Hintergrund zeichnen
            window.draw(bgSprite1);
            window.draw(bgSprite2);

            // Gegner-Spawn Logik
            spawnTimer += deltaTime;
            if (spawnTimer >= spawnInterval) {
                int numEnemiesToSpawn = std::rand() % spawnPositions.size() + 1;
                std::random_device rd;
                std::default_random_engine rng(rd());
                std::shuffle(spawnPositions.begin(), spawnPositions.end(), rng);
                for (int i = 0; i < numEnemiesToSpawn; ++i) {
                    sf::Vector2f spawnPos = spawnPositions[i];
                    enemies.push_back(Enemy(spawnPos.x, spawnPos.y));
                }
                spawnTimer = 0.0f;
            }

            // Gegner aktualisieren und Kollisionen prüfen
            for (auto it = enemies.begin(); it != enemies.end();) {
                if (it->getBounds().top + it->getBounds().height >= 800.f && !it->hasDealtDamage()) {
                    playerHealth -= 10.f;
                    if (playerHealth <= 0) {
                        playerHealth = 0;
                        gameState = GAME_OVER;
                    }
                    it->markAsDamaged();
                }

                if (player.IsEnemyKilled()) {
                    playerScore += 10;
                    player.ResetEnemyKillFlag();
                }
                else {
                    ++it;
                }
            }

            // Highscore aktualisieren
            if (highScore < playerScore) {
                highScore = playerScore;
                highscoreObj.saveHighScore(highScore);
            }

            // UI Texte
            sf::Text playerScoreText;
            playerScoreText.setFont(font);
            playerScoreText.setString("score: " + std::to_string(playerScore));
            playerScoreText.setCharacterSize(24);
            playerScoreText.setFillColor(sf::Color::White);
            playerScoreText.setPosition(950.f, 830.f);

            sf::Text highScoreText;
            highScoreText.setFont(font);
            highScoreText.setString("Highscore: " + std::to_string(highScore));
            highScoreText.setCharacterSize(24);
            highScoreText.setFillColor(sf::Color::White);
            highScoreText.setPosition(950.f, 850.f);

            // Lebensbalken anpassen
            float healthPercentage = playerHealth / maxHealth;
            healthBar.setSize(sf::Vector2f(300.f * healthPercentage, 25.f));

            // Spieler Eingaben 
            player.handleInput(deltaTime);
            player.update(deltaTime, enemies);

            
            player.draw(window);

            // Zeichne Gegner
            for (auto& enemy : enemies) {
                enemy.draw(window);
            }

            //UI
            window.draw(hud);
            window.draw(healthBarBg);
            window.draw(healthBar);
            window.draw(motherShipText);
            window.draw(playerScoreText);
            window.draw(highScoreText);
        }
        else if (gameState == GAME_OVER) {
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}

