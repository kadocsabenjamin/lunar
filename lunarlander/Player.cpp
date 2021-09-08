#include "LunarLander.h"
#include "Player.h"
#include "Explosion.h"

#define _USE_MATH_DEFINES
#include <math.h>


Player::Player(sf::Texture texture[]) {

    body.setSize(sf::Vector2f(BODY_HALF_SIZE*2, BODY_HALF_SIZE*2));
    body.setOrigin(BODY_HALF_SIZE, BODY_HALF_SIZE);
    body.setPosition(START_X, START_Y);
    velocity_y = 0;
    velocity_x = 0;
    landed = false;
    dead = false;
        
    texture[0].loadFromFile("pics/LanderTexture/lander_no.png");
    texture[1].loadFromFile("pics/LanderTexture/lander_flame.png");
    texture[2].loadFromFile("pics/LanderTexture/lander_left_rcs.png");
    texture[3].loadFromFile("pics/LanderTexture/lander_right_rcs.png");
    texture[4].loadFromFile("pics/LanderTexture/lander_left_flame.png");
    texture[5].loadFromFile("pics/LanderTexture/lander_right_flame.png");
    texture[6].loadFromFile("pics/LanderTexture/lander_both_rcs.png");
    texture[7].loadFromFile("pics/LanderTexture/lander_both.png");
    //texture[8].loadFromFile("pics/LanderTexture/lander_dead.png");
    for (size_t i = 0; i < LANDER_PICS; i++)
    {
        this->texture[i] = texture[i];
    }
    fuelbar.setSize(sf::Vector2f(FUELBAR_SIZE_X, FUELBAR_SIZE_Y));
    fuelbar.setPosition(50, 250);
    fuelbar.setFillColor(sf::Color::Red);

    

    buffer.loadFromFile("Sounds/engine.wav");
    engine.setBuffer(buffer);
    engine_soundplay = false;

    rcs_buffer.loadFromFile("Sounds/rcs.wav");
    rcs.setBuffer(rcs_buffer);
    rcs_soundplay = false;

    if (!explosion_buffer.loadFromFile("Sounds/1688.wav")) {
        std::cout << "szar";
    }
    explosion.setBuffer(explosion_buffer);
    explosion_soundplay = false;
}


void Player::Update(sf::VertexArray& lines)
{
    sf::Vector2f movement(0.0f, 0.0f);
    bool flame = false, left_rcs = false, right_rcs = false;
    body.setSize(sf::Vector2f(BODY_HALF_SIZE * 2, BODY_HALF_SIZE * 2));
    float angle = body.getRotation() * (M_PI / 180);
    sf::Vector2f fuelbarpoz = fuelbar.getPosition();
    sf::Vector2f fuelbarsize = fuelbar.getSize();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) {
        dead = false;
        body.setRotation(0);

        

        fuelbar.setSize(sf::Vector2f(FUELBAR_SIZE_X, FUELBAR_SIZE_Y));
        fuelbar.setPosition(50, 250);
        body.setPosition(START_X, START_Y);
    }
    engine_on = false;
    rcs_on = false;
    if (!dead) {
        explosion_soundplay = false;
        dead = OffWindow();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            body.rotate(-ROTATION_SPEED);
            right_rcs = true;
            rcs_on = true;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            body.rotate(ROTATION_SPEED);
            left_rcs = true;
            rcs_on = true;
        }

        if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) && fuelbarsize.y>0) {
            velocity_y -= THRUST * cos(angle);
            velocity_x += THRUST * sin(angle);
            flame = true;
            landed = false;
            engine_on = true;
            
           
            fuelbarsize.y = fuelbarsize.y - FUEL_CONSUMTION;
            fuelbar.setSize(fuelbarsize);
            
            fuelbarpoz.y = fuelbarpoz.y + FUEL_CONSUMTION;
            fuelbar.setPosition(fuelbarpoz);
        }
        
           
        

        if (flame)
        {
            if (!left_rcs && !right_rcs)
                body.setTexture(&texture[1]);
            else if (left_rcs && !right_rcs)
                body.setTexture(&texture[4]);
            else if (!left_rcs && right_rcs)
                body.setTexture(&texture[5]);
            else
                body.setTexture(&texture[7]);
        }
        else
        {
            if (!left_rcs && !right_rcs)
                body.setTexture(&texture[0]);
            else if (left_rcs && !right_rcs)
                body.setTexture(&texture[2]);
            else if (!left_rcs && right_rcs)
                body.setTexture(&texture[3]);
            else
                body.setTexture(&texture[6]);
        }
    }
    else {
        body.setTexture(&texture[8]);
        body.setSize(sf::Vector2f(0, 0));
        if (!explosion_soundplay) {
            Explosion_play();
        }
    }
    
    if (!landed) {
        velocity_y += GRAVITY;
        movement.x = velocity_x;
        movement.y += velocity_y;
        body.move(movement);
    }
    if (LandingDetect(lines) && !dead) {
        dead = !GoodLanding(angle,velocity_y,landed);
        
        velocity_y = 0;
        velocity_x = 0;
    } 
    if (CollisionDetect(lines) && !dead) {
        dead = true;
        velocity_y = 0;
        velocity_x = 0;
    }


    if (engine_on && !engine_soundplay) {
        engine.play();
        engine_soundplay = true;
    }
    else {
        if (!engine_on) {
            engine_soundplay = false;
            engine.stop();
        }
    }
    if (rcs_on && !rcs_soundplay) {
        rcs.play();
        rcs_soundplay = true;
    }
    else {
        if (!rcs_on) {
            rcs_soundplay = false;
            rcs.stop();
        }
    }
}
void Player::Explosion_play() {
    explosion.play();
    explosion_soundplay = true;
}

void Player::Draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(fuelbar);
}

bool Player::CollisionDetect(sf::VertexArray& lines)
{
    sf::Vector2f position(0.0f, 0.0f);
    position = body.getPosition();
    

    for (int i = 2; i < LANDINGSITE2; ++i)
    {
        float x = lines[i + 1].position.x - lines[i].position.x;
        float y = lines[i + 1].position.y - lines[i].position.y;
        float m = y / x;
        float y_addition = 0;
        for (int j = lines[i].position.x; j < lines[i + 1].position.x; ++j)
        {
            if ((int)position.x == j && (int)position.y + BODY_HALF_SIZE - 8 >= lines[i].position.y + y_addition)
            {
                body.setPosition(position.x, lines[i].position.y + y_addition - BODY_HALF_SIZE + 8);
                return true;
            }
            y_addition += m;
        }
    }
    return false;
}

bool Player::LandingDetect(sf::VertexArray& lines)
{
    sf::Vector2f position(0.0f, 0.0f);
    position = body.getPosition();

    for (int i = lines[LANDINGSITE1].position.x; i < lines[LANDINGSITE1+1].position.x; ++i)
    {

        if ((int)position.x == i && (int)position.y + BODY_HALF_SIZE - 8 >= lines[LANDINGSITE1].position.y)
        {
            body.setPosition(position.x, lines[LANDINGSITE1].position.y - BODY_HALF_SIZE + 8);
            return true;
        }
    } 
    for (int i = lines[LANDINGSITE2].position.x; i < lines[LANDINGSITE2+1].position.x; ++i)
    {
        if ((int)position.x == i && (int)position.y + BODY_HALF_SIZE - 8 >= lines[LANDINGSITE2].position.y)
        {
            body.setPosition(position.x, lines[LANDINGSITE2].position.y - BODY_HALF_SIZE + 8);
            return true;
        }
    }
    return false;
}

bool Player::GoodLanding(float angle,float velocity_y,bool& landed)
{
    angle /= (M_PI / 180);
    if ((angle < GOOD_ANGLE || angle > 360 - GOOD_ANGLE) && velocity_y < 0.5) {
        body.setRotation(0);
        landed = true;
        return true;
    }
    return false;
}

bool Player::OffWindow()
{
    sf::Vector2f position(0.0f, 0.0f);
    position = body.getPosition();
    if(position.x<0 || position.x>SCREEN_SIZE_X || position.y<0 || position.y>SCREEN_SIZE_Y){
        return true;
    }
    return false;
}

