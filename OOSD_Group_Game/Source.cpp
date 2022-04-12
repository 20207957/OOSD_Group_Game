#include <iostream>
#include "SFML/graphics.hpp"
#include "SFML/system.hpp"
#include "SFML/window.hpp"

using namespace std;

//classes start
class gamePlayer {
public:
    float playerX;
    float playerY;
    int PlayerSpeed;
    bool playerUp;
    bool playerLeft;
    bool playerRight;

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
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;
    float inGameGravity;

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
    sf::Texture floorTex;
public:
    //sprites
    sf::Sprite player;
    sf::Sprite floor;

    spritesAndTextures()
    {
        cout << "spritesAndTextures Constructor" << endl;

        playerTex.loadFromFile("images/player.png");
        floorTex.loadFromFile("images/floor.jpg");
        player.setTexture(playerTex);
        floor.setTexture(floorTex);
        playerTex.setSmooth(true);
        floorTex.setSmooth(true);
        player.scale(2, 2);
        floor.scale(4, 2);
        floor.setPosition(1.0f, 775.0f);
    }

    ~spritesAndTextures()
    {
        cout << "spritesAndTextures Destructor" << endl;
    }
};
//classes end

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game");

    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    gamePlayer player;
    spritesAndTextures sat;
    gameGravity gravity;


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

        //Clear window and draw new
        window.clear();
        sat.player.setPosition(player.playerX, player.playerY);
        window.draw(sat.player);
        window.draw(sat.floor);
        window.display();
    }
    return 0;
}
