#include "LunarLander.h"
#include "Menuc.h"

Menuc::Menuc(int x)
{
	selectedMenu = 0;
	if (!font.loadFromFile("font/arial.ttf"))
	{
		// error...
	}


	if (x == 0) {
		fontsize = MENU_FONTSIZE;
		
		stringcount = MAINMENUCOUNT;
		menu_strings[0] = "PLAY";
		menu_strings[1] = "EXIT";
		
		texturecount = 1;
		menuTexture[0].loadFromFile("pics/mainmenu.png");

		menutexture_size[0] = sf::Vector2f(SCREEN_SIZE_X - SCREEN_SIZE_X / 5, SCREEN_SIZE_X / 10 - SCREEN_SIZE_X / 5 / 10);

		menutexture_position[0] = sf::Vector2f(100,50);
	}
	if (x == 1) {
		fontsize = MENU_FONTSIZE * 0.6;

		stringcount = PLAYMENUCOUNT;
		menu_strings[0] = "moon lander";
		menu_strings[1] = "cargo ship";
		menu_strings[2] = "go to main menu";

		texturecount = 2;
		menuTexture[0].loadFromFile("pics/LanderTexture/lander_no.png");
		menuTexture[1].loadFromFile("pics/LongLander/spaceship_left_down.png");

		menutexture_size[0] = sf::Vector2f(BODY_HALF_SIZE * 4, BODY_HALF_SIZE * 4);
		menutexture_size[1] = sf::Vector2f(LONG_LANDER_BODY_SIZE_X * 2, LONG_LANDER_BODY_SIZE_Y * 2);

		menutexture_position[0] = sf::Vector2f(750, 250);
		menutexture_position[1] = sf::Vector2f(750, 450);
	}
	if (x == 2) {
		fontsize = MENU_FONTSIZE * 0.6;

		stringcount = PAUSEMENUCOUNT;
		menu_strings[0] = "continue";
		menu_strings[1] = "back to main menu";

		texturecount = 1;
		menuTexture[0].loadFromFile("pics/mainmenu.png");

		menutexture_size[0] = sf::Vector2f(SCREEN_SIZE_X - SCREEN_SIZE_X / 5, SCREEN_SIZE_X / 10 - SCREEN_SIZE_X / 5 / 10);

		menutexture_position[0] = sf::Vector2f(100, 50);
	}

	for (int i = 0; i < stringcount; i++)
	{
		menu[i].setFont(font);
		menu[i].setFillColor(sf::Color::White);
		menu[i].setCharacterSize(fontsize);
		menu[i].setPosition(SCREEN_SIZE_X / 5 - menu[i].getLocalBounds().width / 2, (SCREEN_SIZE_Y / (stringcount + 1)) * (1 + i) - menu[i].getLocalBounds().height / 2);
		menu[i].setString(menu_strings[i]);
	}
	menu[0].setFillColor(sf::Color::Red);

	for (int i = 0; i < texturecount; i++)
	{
		texture[i] = menuTexture[i];
		body[i].setTexture(&menuTexture[i]);
		body[i].setPosition(menutexture_position[i]);
		body[i].setSize(menutexture_size[i]);
	}
}

Menuc::~Menuc()
{
}

void Menuc::Draw(sf::RenderWindow& window,int x) {
	if (x == 0) {
		for (int i = 0; i < stringcount; ++i)
		{
			window.draw(menu[i]);
		}
		if (selectedMenu < texturecount)
		{
			window.draw(body[selectedMenu]);
		}
	}
	else
	{
		for (int i = 0; i < stringcount; ++i)
		{
			window.draw(menu[i]);
		}
		for (int i = 0; i < texturecount; ++i)
		{
			window.draw(body[i]);
		}
	}
}

void Menuc::Update(sf::Event event) {
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Up)
		{
			MoveUp();
		}
		if (event.key.code == sf::Keyboard::Down)
		{
			MoveDown();
		}
	}
}

void Menuc::MoveUp() {
	
	if (selectedMenu - 1 >= 0)
	{
		menu[selectedMenu].setFillColor(sf::Color::White);
		selectedMenu--;
		menu[selectedMenu].setFillColor(sf::Color::Red);
	}
	
}

void Menuc::MoveDown() {
	if (selectedMenu < stringcount-1)
	{
		menu[selectedMenu].setFillColor(sf::Color::White);
		selectedMenu++;
		menu[selectedMenu].setFillColor(sf::Color::Red);
	}
}

bool Menuc::Play(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Return)
		{
			return true;
		}
	}
	return false;
}
bool Menuc::Pause(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Escape)
		{
			return true;
		}
	}
	return false;
}

int Menuc::Play_select(sf::Event event)
{
	if (event.type == sf::Event::KeyReleased) {
		if (event.key.code == sf::Keyboard::Return)
		{
			return selectedMenu;
		}
	}
	return -1;
}

void Menuc::Exit(sf::RenderWindow& window)
{
	if (selectedMenu == MAINMENUCOUNT-1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Return)) {
		window.close();
	}
}


