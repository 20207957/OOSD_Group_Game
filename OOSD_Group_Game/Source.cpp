#include <iostream>
#include "SFML/graphics.hpp"
#include "SFML/system.hpp"
#include "SFML/window.hpp"
#include <vector>
#include <dos.h> 

unsigned int microseconds;
using namespace std;

int plife = 3;
int hpMax = 3;

//classes start
class SpriteSetup //Inheritence  
{
public:
    sf::Sprite Sprite;

    SpriteSetup(std::string textureFilename) {
        cout << "SpriteSetup Constructor (" << textureFilename << ")" << endl;

        try { //Exeption Handling
            if (_texture.loadFromFile("images/" + textureFilename)) {
                cout << textureFilename << " loaded successfully." << endl;
            }
            else {
                throw " - Sprite could not be found.";
            }
        }
        catch (const char* msg) {
            cout << textureFilename + msg << endl;
        }

        Sprite.setTexture(_texture);
        _texture.setSmooth(true);
    }

    virtual void setupSprite() = 0; //Polymorphism

    ~SpriteSetup()
    {
        cout << "SpriteSetup Destructor" << endl;
    }

private:
    sf::Texture _texture;
};

class gamePlayer : public SpriteSetup
{
public:
    float playerX, playerY;
    int PlayerSpeed;
    bool playerUp, playerLeft, playerRight;

    gamePlayer(std::string textureFilename) : SpriteSetup(textureFilename)
    {
        cout << "gamePlayer Constructor" << endl;
        playerX = 400.0f;
        playerY = 600.0f;
        PlayerSpeed = 5;
        playerUp = false;
        playerLeft = false;
        playerRight = false;
    }

    void setupSprite() {
        Sprite.scale(2, 2);
    }

    ~gamePlayer()
    {
        cout << "gamePlayer Destructor" << endl;
    }
};

class Background : public SpriteSetup
{
public:
    Background(std::string textureFilename) : SpriteSetup(textureFilename)
    {
        cout << "Background Constructor" << endl;
    }

    void setupSprite() {
        Sprite.setScale(1.0f, 1.25f);
        Sprite.setPosition(1.0, -40.0f);
    }

    ~Background()
    {
        cout << "Background Destructor" << endl;
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

class sfComponents
{
public:
    //Sprites
    sf::Sprite* heartsSprite;
    sf::Sprite life;
    sf::Sprite block;
    sf::Sprite block2;
    sf::Sprite hearts;

    //Textures
    sf::Texture blockTex;
    sf::Texture blockTex2;
    sf::Texture lifeTex;
    sf::Texture heartsTex;

    //Font and Text
    sf::Font font;
    sf::Text lifedisplay;

    //TIME
    sf::Clock clock;
    sf::Time second = sf::seconds(35.f);
};

class ImgSet : public sfComponents
{ 
public:
    sf::Sprite* heartsSprite;
    int v = 0;

    //Conversion int to string
    string lstring = to_string(plife);

    ImgSet()
    {
        cout << "Images Set Constructor" << endl;

        //Life and Life in text
        lifeTex.loadFromFile("images/heart.png");
        life.setTexture(lifeTex);
        lifeTex.setSmooth(true);
        life.scale(0.139, 0.139);
        life.setPosition(45, 55);

        font.loadFromFile("images/font.ttf");
        lifedisplay.setFont(font);
        lifedisplay.setString(lstring);
        lifedisplay.setCharacterSize(50);
        lifedisplay.setFillColor(sf::Color::White);
        lifedisplay.setStyle(sf::Text::Bold);
        lifedisplay.setPosition(72.5, 65);

        //Block
        blockTex.loadFromFile("images/lava.png");
        block.setTexture(blockTex);
        blockTex.setSmooth(true);
        block.scale(0.2, 0.2);
        block.setPosition(500, 600);

        //Block2
        blockTex2.loadFromFile("images/lava.png");
        block2.setTexture(blockTex);
        blockTex2.setSmooth(true);
        block2.scale(0.2, 0.2);
        block2.setPosition(100, 600);

        //Hearts
        heartsTex.loadFromFile("images/heart.png");
        hearts.setTexture(heartsTex);
        hearts.setScale(0.10f, 0.10f);
        heartsTex.setSmooth(true);
    }

    ~ImgSet()
    {

    }
};

class exceptions : public sfComponents
{
public:
    exceptions() {
        int error = 404;

        string x = "Locate folder .tff";
        try { //Exeption Handling
            cout << "Chiecking for Exceptions..." << endl;

            if (!(font.loadFromFile("images/font.ttf"))) {
                cout << "Font loaded unsuccessfully." << endl;

                throw error;
            }
        }
        catch (int error) {
            cout << "Locate folder .tff" << endl;
        }
    }
};

class spritesAndTextures {
private:
    //declare textures
    sf::Texture playerTex;
    sf::Texture backgroundTex;
    sf::Texture coinTex;
    sf::Texture fallTex;
public:
    //declare sprites
    sf::Sprite player;
    sf::Sprite background;
    sf::Sprite coin;
    sf::Sprite fall;

    spritesAndTextures()
    {
        cout << "spritesAndTextures Constructor" << endl;

        //load textures
        playerTex.loadFromFile("images/player.png");
        coinTex.loadFromFile("images/coin.png");
        backgroundTex.loadFromFile("images/background.jpg");
        fallTex.loadFromFile("images/missile.png");

        //set textures
        player.setTexture(playerTex);
        background.setTexture(backgroundTex);
        coin.setTexture(coinTex);
        fall.setTexture(fallTex);

        //sprite and texture properties
        player.scale(2, 2);
        background.setScale(1.0f, 1.25f);
        coin.setScale(0.25f, 0.25f);
        background.setPosition(1.0, -40.0f);
        playerTex.setSmooth(true);
        backgroundTex.setSmooth(true);
        coinTex.setSmooth(true);
        fall.setScale(0.25, 0.25f);
    }
    ~spritesAndTextures()
    {
        cout << "spritesAndTextures Destructor" << endl;
    }
};

class fallGravity {
public:
    float velocityY,velocityX, accelerationY, accelerationX, inFallGravity;

    fallGravity() {
        cout << "fallGravity Constructor" << endl;
        velocityY = 0;
        velocityX = 0;
        accelerationY = 0;
        accelerationX = 0;
        inFallGravity = 1;
    }

    ~fallGravity()
    {
        cout << "fallGravity Destructor" << endl;
    }
};

class fall {
private:
    sf::Sprite* fallSprite;

public:
    float x, y;
    fall(sf::Sprite* fallTex) {
        this->fallSprite = fallTex;
        y = 0;
        x = rand() % 1000;
        cout << "\nspawn fall" << endl;
    }
    void draw(sf::RenderWindow* window) {
        fallSprite->setPosition(x, y);
        window->draw(*fallSprite);
    }
    sf::FloatRect getRect() {
        return fallSprite->getGlobalBounds();
    }

    fall()
    {
        
    }

    ~fall()
    {

    }

};

class hearts : public sfComponents {

public:
    float x, y;

    hearts(sf::Sprite* heartsTex) {
        this->heartsSprite = heartsTex;

        if (second > clock.getElapsedTime()) {
            y = 700;
            x = rand() % 800;
            return;

            clock.restart();
        }
    }
    void draw(sf::RenderWindow* window) {
        heartsSprite->setPosition(x, y);
        window->draw(*heartsSprite);
    }
    sf::FloatRect getRect() {
        return heartsSprite->getGlobalBounds();
    }
};

class Coin {
private:
    sf::Sprite* coinSprite;

public:
    float x, y;
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
}; //classes end

//player intersect coins
bool isIntersects(sf::FloatRect a, sf::FloatRect b) {
    if (a.intersects(b)) {
        return true;
    }
    return false;
}

//player intersect block
bool collide(sf::FloatRect c, sf::FloatRect d) {

    if (c.intersects(d)) {
        return true;
    }
    return false;
}

//player intersect block2
bool collide2(sf::FloatRect g, sf::FloatRect h) {

    if (g.intersects(h)) {
        return true;
    }
    return false;
}

//player intersect falls
bool ifIntersects(sf::FloatRect e, sf::FloatRect f) {
    if (e.intersects(f)) {
        return true;
    }
    return false;
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Game");
    srand(time(NULL));
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    window.setKeyRepeatEnabled(false);

    //setup sprites
    Background bg("background.jpg");
    bg.setupSprite();
    gamePlayer player("player.png");
    player.setupSprite();

    //start classes
    spritesAndTextures sat;
    gameGravity gravity;
    ImgSet hp;
    fallGravity fallingGravity;
    fall f;

    sat.fall.move(sf::Vector2f(0, 10));

    //declare vector arrays
    vector<Coin> coins;
    vector<hearts> life;
    vector<fall> falls;

    //load font
    sf::Font font;
    font.loadFromFile("images/font.ttf");
    cout << "Font Loaded" << endl;

    //score
    int score = 0;
    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setPosition(30, 10);
    scoreText.setCharacterSize(34);
    scoreText.setFillColor(sf::Color(255, 0, 0));

    //instructions
    cout << "\n\n------------------------------------------" << endl;
    cout << "Welcome to our game!\nUse the WASD keys to play\nCollect coins to increase your score\nDodge the falling objects from the sky\nYou have 3 lives\nGood Luck!" << endl;
    cout << "------------------------------------------" << endl;

    //main game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            //If key is pressed - movement start
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
            //If key has been released - movement stop
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

            //player flip
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                sat.player.setScale(-2, 2);
            }
            else
            {
                sat.player.setScale(2, 2);
            }

            //player jump
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
        if (player.playerY < 600) player.playerUp = false;
        if (player.playerY < 575) player.playerY = 575;


        //Gravity function
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

        //Collision with block
        if (hp.block.getGlobalBounds().intersects(sat.player.getGlobalBounds()))
        {
            cout << "Collision" << endl;
            plife--;
            hp.block.setScale(0, 0);
            cout << plife << endl;

            hp.lifedisplay.setString(to_string(plife));

            string lstring = to_string(plife);
            window.draw(hp.lifedisplay);
        }

        //Collision with block2
        if (hp.block2.getGlobalBounds().intersects(sat.player.getGlobalBounds()))
        {
            cout << "Collision" << endl;
            plife--;
            hp.block2.setScale(0, 0);
            cout << plife << endl;

            hp.lifedisplay.setString(to_string(plife));

            string lstring = to_string(plife);
            window.draw(hp.lifedisplay);
        }
        //random number generator - +1 to vector
        if (rand() % 30 == 1 && coins.size() < 10) {
            coins.push_back(Coin(&sat.coin));
        }

        if (rand() % 30 == 1 && falls.size() < 10) {
            falls.push_back(fall(&sat.fall));
        }

        //random Hearts
        if (plife < 2) {
            sf::Clock clock;
            sf::Time second = sf::seconds(1.0f);
            sf::Time t2 = clock.restart();

            if (clock.getElapsedTime() > clock.getElapsedTime()) {

                if (rand() % 30 == 1 && life.size() < 1) {
                    life.push_back(hearts(&hp.hearts));

                    t2;
                }
            }
        }

        //Clear window and draw new
        window.clear();
        sat.player.setPosition(player.playerX, player.playerY);
        window.draw(sat.background);
        hp.block.setPosition(500, 600);
        window.draw(sat.player);
        window.draw(hp.block);
        window.draw(hp.block2);
        window.draw(hp.life);
        window.draw(hp.lifedisplay);

        //show score
        scoreText.setString("Score: " + to_string(score));
        window.draw(scoreText);

        //Make coins
        for (int i = 0; i < coins.size(); i++) {
            coins[i].draw(&window);

            //if collide with coin
            if (isIntersects(coins[i].getRect(), sat.player.getGlobalBounds())) {
                coins.erase(coins.begin() + i);
                score++;
            }
        }

        //Make falls
        for (int i = 0; i < falls.size(); i++) {
            falls[i].draw(&window);

            //if collide with fall
            if (ifIntersects(falls[i].getRect(), sat.player.getGlobalBounds())) {
                falls.erase(falls.begin() + i);
                score++;

            }
        }

        for (int j = 0; j < life.size(); j++) {
            life[j].draw(&window);

            //if collide with  hearts
            if (isIntersects(life[j].getRect(), sat.player.getGlobalBounds())) {
                life.erase(life.begin() + j);
                plife++;

                hp.lifedisplay.setString(to_string(plife));

                string lstring = to_string(plife);
                window.draw(hp.lifedisplay);

                cout << "life up" << endl;
                cout << plife << endl;
            }
        }

        if (plife == 0)
        {
            cout << "GAME OVER! Your score was:" << endl;
            cout << score << endl;
            cout << "\n\n\n\n" << endl;
            window.close();
        }
        window.display();
    }
    return 0;
}