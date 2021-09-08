#pragma once



class LongLander
{
public:
    LongLander(sf::Texture texture[]);
    void Update(sf::VertexArray& lines);
    void Draw(sf::RenderWindow& window);
    bool CollisionDetect(sf::VertexArray& lines);
    bool LandingDetect(sf::VertexArray& lines);
    bool GoodLanding(float angle, float velocity_y, bool& landed);
    bool OffWindow();
    sf::Texture texture[LONG_LANDER_PICS];
private:
    
    sf::RectangleShape body;
    sf::RectangleShape fuelbar;
    float velocity_y;
    float velocity_x;
    bool landed;
    bool dead;
    bool engine_on;
    bool engine_soundplay;
    sf::SoundBuffer buffer;
    sf::Sound engine;
};


