#include <iostream>
#include "SFML/graphics.hpp"
#include "SFML/system.hpp"
#include "SFML/window.hpp"
#include <vector>

using namespace std;

//classes start
class gamePlayer {
public:
    float playerX, playerY;
    int PlayerSpeed;
    bool playerUp, playerLeft, playerRight;

    gamePlayer()
    {
        cout << "gamePlayer Constructor" << endl;
        playerX = 400.0f;
        playerY = 600.0f;
        PlayerSpeed = 5;
        playerUp = false;
        playerLeft = false;
        playerRight = false;
    }

    ~gamePlayer()
    {
        cout << "gamePlayer Destructor" << endl;
    }

};

class gameGravity {
public:
    float velocityX, velocityY, accelerationX, accelerationY, inGameGravity;

    gameGravity()
    {
        cout << "gameGravity Constructor" << endl;
        velocityX = 0;
        velocityY = 0;
        accelerationX = 0;
        accelerationY = 0;
        inGameGravity = 1;
    }

    ~gameGravity()
    {
        cout << "gameGravity Destructor" << endl;
    }
};

class spritesAndTextures {
private:
    //textures
    sf::Texture playerTex;
    sf::Texture backgroundTex;
    sf::Texture coinTex;
public:
    //sprites
    sf::Sprite player;
    sf::Sprite background;
    sf::Sprite coin;

    spritesAndTextures()
    {
        cout << "spritesAndTextures Constructor" << endl;

        playerTex.loadFromFile("images/player.png");
        coinTex.loadFromFile("images/coin.png");
        backgroundTex.loadFromFile("images/background.jpg");

        player.setTexture(playerTex);
        background.setTexture(backgroundTex);
        playerTex.setSmooth(true);
        backgroundTex.setSmooth(true);
        player.scale(2, 2);
        background.setScale(1.0f, 1.25f);
        background.setPosition(1.0, -40.0f);

        coin.setTexture(coinTex);
        coin.setScale(0.25f, 0.25f);
    }

    ~spritesAndTextures()
    {
        cout << "spritesAndTextures Destructor" << endl;
    }
};

class Coin {
    sf::Sprite* coinSprite;

public:
    float x;
    float y;
    Coin(sf::Sprite* coinTex) {
        this->coinSprite = coinTex;
        y = 720;
        x = rand() % 800;
    }
    void draw(sf::RenderWindow* window) {
        coinSprite->setPosition(x, y);
        window->draw(*coinSprite);
    }
    sf::FloatRect getRect() {
        return coinSprite->getGlobalBounds();
    }
};

//classes end

bool isIntersects(sf::FloatRect a, sf::FloatRect b) {
    if (a.intersects(b)) {
        return true;
    }
    return false;
}

int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    gamePlayer player;
    spritesAndTextures sat;
    gameGravity gravity;

    vector<Coin> coins;

    sf::Font font;
    font.loadFromFile("images/font.ttf");


    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setPosition(30, 10);
    scoreText.setCharacterSize(34);
    scoreText.setFillColor(sf::Color(255, 0, 0));


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //If key is pressed
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:player.playerUp = true; break;
                case sf::Keyboard::A:player.playerLeft = true; break;
                case sf::Keyboard::D:player.playerRight = true; break;
                default: break;
                }
            }

            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::W:player.playerUp = false; break;
                case sf::Keyboard::A:player.playerLeft = false; break;
                case sf::Keyboard::D:player.playerRight = false; break;
                default: break;
                }
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                sat.player.setScale(-2, 2);
            }
            else
            {
                sat.player.setScale(2, 2);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                gravity.velocityY = -10;
            }
        }


        //Update player
        if (player.playerLeft) player.playerX -= player.PlayerSpeed;
        if (player.playerRight) player.playerX += player.PlayerSpeed;
        if (player.playerUp) player.playerY -= player.PlayerSpeed;

        //Player boundaries
        if (player.playerX < 0) player.playerX = 0;
        if (player.playerX > (int)window.getSize().x) player.playerX = window.getSize().x;
        if (player.playerY < 0) player.playerY = 0;
        if (player.playerY > (int)window.getSize().y) player.playerY = window.getSize().y;
        if (player.playerY < 550) player.playerY = 600;

        void gameGravityFun();
        {
            if (player.playerY < 680)
                gravity.velocityY += gravity.inGameGravity;
            else if (player.playerY > 680)
                player.playerY = 680;

            gravity.velocityX += gravity.accelerationX;
            gravity.velocityY += gravity.accelerationY;

            player.playerX += gravity.velocityX;
            player.playerY += gravity.velocityY;
        }

        if (rand() % 30 == 1 && coins.size() < 10) {
            coins.push_back(Coin(&sat.coin));
        }

        //Clear window and draw new
        window.clear();
        sat.player.setPosition(player.playerX, player.playerY);
        window.draw(sat.background);
        window.draw(sat.player);


        scoreText.setString("Score: " + to_string(score));
        window.draw(scoreText);

        for (int i = 0; i < coins.size(); i++) {
            coins[i].draw(&window);
            
            //if collide with coin
            if (isIntersects(coins[i].getRect(), sat.player.getGlobalBounds())) {
                coins.erase(coins.begin() + i);
                score++;
            }
        }

        window.display();
    }
    return 0;
}


