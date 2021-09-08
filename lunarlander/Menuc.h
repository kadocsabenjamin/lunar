#pragma once
class Menuc
{
public:
	Menuc(int x);
	~Menuc();
	void Draw(sf::RenderWindow& window,int count);
	void Update(sf::Event event);
	void MoveUp();
	void MoveDown();


	bool Play(sf::Event event);
	bool Pause(sf::Event event);
	
	void Exit(sf::RenderWindow& window);
	int Play_select(sf::Event event);


private:
	sf::Font font;
	sf::Text menu[MENUMAXCOUNT];
	sf::RectangleShape body[MENUMAXCOUNT];
	sf::Texture texture[MENUMAXCOUNT];
	int selectedMenu;

	int stringcount;
	int texturecount;
	int fontsize;
	std::string menu_strings[MENUMAXCOUNT];
	sf::Texture menuTexture[MENUMAXCOUNT];
	sf::Vector2f menutexture_size[MENUMAXCOUNT];
	sf::Vector2f menutexture_position[MENUMAXCOUNT];
};
