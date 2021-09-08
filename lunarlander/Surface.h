#pragma once
class Surface
{
public:
	Surface(sf::VertexArray& lines, sf::Texture texture[]);


	
	sf::Texture texture[LANDING_SITE_PICS];
	sf::RectangleShape landingsite;

	void Draw(sf::VertexArray& lines, sf::RenderWindow& window);
};

