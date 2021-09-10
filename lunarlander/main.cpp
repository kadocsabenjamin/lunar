#include "LunarLander.h"

#include "LongLander.h"
#include "Player.h"
#include "Surface.h"

#include "Menuc.h" 

#include <Windows.h>


#include "Explosion.h" //

int main()
{
//git
    

    sf::RenderWindow window(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Lunar Lander"); //, sf::Style::Fullscreen
    sf::Texture playerTexture[LANDER_PICS];
    sf::Texture longlanderTexture[LONG_LANDER_PICS];

    Player player(playerTexture);
    LongLander longlander(longlanderTexture);

    srand(time(NULL));

    sf::Texture landingsiteTexture[LANDING_SITE_PICS];
    sf::VertexArray lines(sf::LinesStrip, LINECOUNT);
    Surface surface(lines, landingsiteTexture);

    bool nothing_pressed = true, play_pressed = false, esc_pressed = false;
    int play_selected = -1, esc_select = -1;

    Menuc menuc(0), play_menu(1), pause_menu(2);
    
    
    //MakeExplosionAnimation(window);
    sf::Texture explosionanimationTexture[1];
    sf::Vector2u count = sf::Vector2u(5, 4);
    Explosion explosionanimation(explosionanimationTexture, count,window);

    int explosioncounter = 110;
    int sleepcounter = 0;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();   
            if (play_pressed && play_selected < 0) {
                play_selected = play_menu.Play_select(event);
                play_menu.Update(event);
                
            }
            if (nothing_pressed) {
                play_pressed = menuc.Play(event);
                menuc.Update(event);                
                menuc.Exit(window);
            }
            if (play_selected >= 0) {
                if (menuc.Pause(event))
                {
                    esc_pressed = true;
                }
                if (esc_pressed) {
                    esc_select = pause_menu.Play_select(event);
                    pause_menu.Update(event);
                }
            }
        }
        if (nothing_pressed) {
            menuc.Draw(window, 1);
            
            
        }
        

        if (play_pressed && play_selected < 0) {
            surface.Draw(lines, window);
            nothing_pressed = false;
            play_menu.Draw(window, 0);
        }
        if (play_selected>=0){
            if (esc_pressed) {
                pause_menu.Draw(window,1);
            }
            else {
                if (play_selected == 0) {
                    player.Update(lines);
                    player.Draw(window);
                    if (!player.dead) {
                        explosionanimation.animationend = false;
                        explosionanimation.currentImage = 0;
                    }
                    if (player.dead && !explosionanimation.animationend) {
                        explosionanimation.body.setPosition(player.body.getPosition());
                        //explosionanimation.body.setRotation(player.body.getRotation());
                        if(++explosioncounter>4){
                            explosionanimation.Update();
                            explosioncounter = 0;
                        }
                        explosionanimation.Draw(window);
                    }
                }
                if (play_selected == 1) {
                    longlander.Update(lines);
                    longlander.Draw(window);
                }
                surface.Draw(lines, window);
            }
        }
        if (esc_select == 0) {
            esc_pressed = false;
        }
        if (esc_select == 1 || play_selected == 2) {
            nothing_pressed = true; play_pressed = false; esc_pressed = false;
            play_selected = -1; esc_select = -1;
        }
       
       // explosionanimation.Update();
       // explosionanimation.Draw(window);
        window.display();
        
        if (++sleepcounter==2)
        {
            Sleep(10);
            sleepcounter = 0;
        }
        else
        {
            Sleep(0);
        }
        
        window.clear();
        
        
        
    }

    return 0;
}


