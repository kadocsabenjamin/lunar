#include "LunarLander.h"
#include "Explosion.h"

//Explosion* exppointer;

/*void MakeExplosionAnimation(sf::RenderWindow& window) {
	sf::Texture exlosionTexture[1];
	Explosion explosionAnimation(exlosionTexture, sf::Vector2u(5, 4),window);
}*/

Explosion::Explosion(sf::Texture texture[], sf::Vector2u imageCount, sf::RenderWindow& window)
{
	this->imageCount = imageCount;
	currentImage = 0;
	animationend = false;

	body.setSize(sf::Vector2f(192, 192));
	//body.setPosition(START_X+400, START_Y-100);
	body.setOrigin(100, 100);

	texture[0].loadFromFile("pics/pngwingss.png");
	this->texture[0] = texture[0];
	body.setTexture(&texture[0]);
	//exppointer = this;
	//window.draw(body);
}

void Explosion::Update()
{
	int sizex = body.getSize().x;
	int sizey = body.getSize().y;
	int x = ((currentImage+1) % imageCount.x) * sizex;
	int y = ((currentImage+1) / imageCount.x) * sizex;
	
	//std::cout << x << " - " << y << " - " << imageCount.x << std::endl;
	body.setTextureRect(sf::IntRect(x, y,sizex,sizey));
	//body.setTextureRect(sf::IntRect(0, 0, 192, 192));
	currentImage++;
	if (currentImage >= imageCount.x * imageCount.y) {
		currentImage = 0;
		animationend = true;
	}
	
}

void Explosion::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
