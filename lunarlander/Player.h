#pragma once

class Player
{
public:
    Player(sf::Texture texture[]);
    //~Player();
    void Update(sf::VertexArray& lines);
    void Draw(sf::RenderWindow& window);
    bool CollisionDetect(sf::VertexArray& lines);
    bool LandingDetect(sf::VertexArray& lines);
    
    bool GoodLanding(float angle, float velocity_y, bool& landed);
    bool OffWindow();
    bool dead;
    sf::RectangleShape body;

private:
    sf::Texture texture[LANDER_PICS];
    
    sf::RectangleShape fuelbar;
    float velocity_y;
    float velocity_x;
    bool landed;
    

    bool engine_on;
    bool engine_soundplay;
    bool rcs_on;
    bool rcs_soundplay;
    bool explosion_soundplay;
    sf::SoundBuffer buffer;
    sf::SoundBuffer explosion_buffer;
    sf::SoundBuffer rcs_buffer;
    sf::Sound engine;
    sf::Sound explosion;
    sf::Sound rcs;


    void Explosion_play();
};

