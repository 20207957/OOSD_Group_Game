#include <iostream>
#include "SFML/graphics.hpp"
#include "SFML/system.hpp"
#include "SFML/window.hpp"

using namespace std;

//classes start
class gamePlayer {
public:
    string playerName;
    float playerX;
    float playerY;
    int PlayerSpeed;
    bool playerUp;
    bool playerLeft;
    bool playerRight;
};

class gameGravity {
public:
    float velocityX;
    float velocityY;
    float accelerationX;
    float accelerationY;
    float inGameGravity;
};

class spritesAndTextures {
public:
    //textures
    sf::Texture playerTex;
    sf::Texture floorTex;
    //sprites
    sf::Sprite player;
    sf::Sprite floor;

};
//classes end

    int main()
    {
        sf::RenderWindow window(sf::VideoMode(800, 800), "Game");

        window.setVerticalSyncEnabled(true);
        window.setKeyRepeatEnabled(false);

        gamePlayer player;
        ///////player.playerName
        player.playerX = 400.0f;
        player.playerY = 680.0f;
        player.PlayerSpeed = 5;
        player.playerUp = false;
        player.playerLeft = false;
        player.playerRight = false;

        spritesAndTextures sat;
        sat.playerTex.loadFromFile("images/player.png");
        sat.floorTex.loadFromFile("images/floor.jpg");
        sat.player.setTexture(sat.playerTex);
        sat.floor.setTexture(sat.floorTex);
        sat.playerTex.setSmooth(true);
        sat.floorTex.setSmooth(true);
        sat.player.scale(2, 2);
        sat.floor.scale(4, 2);
        sat.floor.setPosition(1.0f, 775.0f);

        gameGravity gravity;
        gravity.velocityX = 0;
        gravity.velocityY = 0;
        gravity.accelerationX = 0;
        gravity.accelerationY = 0;
        gravity.inGameGravity = 1;

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
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

            //Screen boundaries
            if (player.playerX < 0) player.playerX = 0;
            if (player.playerX > (int)window.getSize().x) player.playerX = window.getSize().x;
            if (player.playerY < 0) player.playerY = 0;
            if (player.playerY > (int)window.getSize().y) player.playerY = window.getSize().y;

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