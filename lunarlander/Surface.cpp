#include "LunarLander.h"
#include "Surface.h"


Surface::Surface(sf::VertexArray& lines, sf::Texture texture[])
{
    landingsite.setSize(sf::Vector2f(160, 16));
    
    texture[0].loadFromFile("pics/landingsite/landing_site_v2.png");
    this->texture[0] = texture[0];
    landingsite.setTexture(&texture[0]);

    lines[0].position = sf::Vector2f(0, rand() % SCREEN_SIZE_Y);
    lines[LANDINGSITE1].position = sf::Vector2f(100, 700);  //landing zone
    lines[2].position = sf::Vector2f(300, 700);     //landing zone
    lines[3].position = sf::Vector2f(350, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[4].position = sf::Vector2f(420, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[5].position = sf::Vector2f(500, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[6].position = sf::Vector2f(550, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[7].position = sf::Vector2f(630, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[8].position = sf::Vector2f(740, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[9].position = sf::Vector2f(800, 200 + rand() % (SCREEN_SIZE_Y - 200));
    lines[10].position = sf::Vector2f(850, 200 + rand() % (SCREEN_SIZE_Y - 200));
    int p = 200 + rand() % (SCREEN_SIZE_Y - 200);
    landingsite.setPosition(945, p-12);
    lines[11].position = sf::Vector2f(940, p+4);
    lines[LANDINGSITE2].position = sf::Vector2f(950, p);  //landing zone2
    lines[13].position = sf::Vector2f(1100, p);   //landing zone2
    lines[14].position = sf::Vector2f(1110, p + 4);
    lines[15].position = sf::Vector2f(1200, rand() % SCREEN_SIZE_Y);
}



void Surface::Draw(sf::VertexArray& lines, sf::RenderWindow& window) {
    window.draw(lines);
    window.draw(landingsite);
}