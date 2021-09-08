#pragma once


//void MakeExplosionAnimation(sf::RenderWindow& window);

class Explosion
{
public:
	Explosion(sf::Texture texture[], sf::Vector2u imageCount, sf::RenderWindow& window);

	void Update();
	void Draw(sf::RenderWindow& window);

	

	sf::Vector2u imageCount;
	int currentImage;


	bool animationend;

	sf::Texture texture[1];
	sf::RectangleShape body;
};


//extern Explosion* exppointer;