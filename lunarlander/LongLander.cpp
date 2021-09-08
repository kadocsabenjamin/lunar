
#include "LunarLander.h"


#include "LongLander.h"


#define _USE_MATH_DEFINES
#include <math.h>

LongLander::LongLander(sf::Texture texture[]) {

    body.setSize(sf::Vector2f(LONG_LANDER_BODY_SIZE_X, LONG_LANDER_BODY_SIZE_Y));
    body.setOrigin(LONG_LANDER_BODY_SIZE_X/2, LONG_LANDER_BODY_SIZE_Y/2);
    body.setPosition(START_X, START_Y);
    velocity_y = 0;
    velocity_x = 0;
    landed = false;
    dead = false;
    texture[0].loadFromFile("pics/LongLander/spaceship_none.png");
    texture[1].loadFromFile("pics/LongLander/spaceship_down.png");
    texture[2].loadFromFile("pics/LongLander/spaceship_left.png");
    texture[3].loadFromFile("pics/LongLander/spaceship_right.png");
    texture[4].loadFromFile("pics/LongLander/spaceship_left_down.png");
    texture[5].loadFromFile("pics/LongLander/spaceship_right_down.png");
    texture[6].loadFromFile("pics/LongLander/spaceship_left_right.png");
    texture[7].loadFromFile("pics/LongLander/spaceship_both.png");
    for (size_t i = 0; i < LONG_LANDER_PICS; i++)
    {
        this->texture[i] = texture[i];
    }

    fuelbar.setSize(sf::Vector2f(FUELBAR_SIZE_X, FUELBAR_SIZE_Y));
    fuelbar.setPosition(50, 250);
    fuelbar.setFillColor(sf::Color::Red);

    buffer.loadFromFile("Sounds/engine.wav");
    engine.setBuffer(buffer);
    engine_soundplay = false;
    
}

void LongLander::Update(sf::VertexArray& lines)
{
    sf::Vector2f movement(0.0f, 0.0f);
    bool mainengine = false, left_engine = false, right_engine = false;
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
    if (!dead) {
        dead = OffWindow();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && fuelbarsize.y > 0) {
            right_engine = true;
            left_engine = true;
            mainengine = true;
            landed = false;
            velocity_y -= 6 * LONG_LANDER_THRUST * cos(angle);
            velocity_x += 6 * LONG_LANDER_THRUST * sin(angle);
            fuelbarsize.y = fuelbarsize.y - 6*LL_FUEL_CONSUMTION;
            fuelbar.setSize(fuelbarsize);

            fuelbarpoz.y = fuelbarpoz.y + 6 * LL_FUEL_CONSUMTION;
            fuelbar.setPosition(fuelbarpoz);
        }
        else {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && fuelbarsize.y > 0) {
                body.rotate(-LL_ROTATION_SPEED);
                right_engine = true;
                landed = false;
                velocity_y -= 2 * LONG_LANDER_THRUST * cos(angle);
                velocity_x += 2 * LONG_LANDER_THRUST * sin(angle);
                fuelbarsize.y = fuelbarsize.y - 1 * LL_FUEL_CONSUMTION;
                fuelbar.setSize(fuelbarsize);

                fuelbarpoz.y = fuelbarpoz.y + 1 * LL_FUEL_CONSUMTION;
                fuelbar.setPosition(fuelbarpoz);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && fuelbarsize.y > 0) {
                body.rotate(LL_ROTATION_SPEED);
                left_engine = true;
                landed = false;
                velocity_y -= 2 * LONG_LANDER_THRUST * cos(angle);
                velocity_x += 2 * LONG_LANDER_THRUST * sin(angle);
                fuelbarsize.y = fuelbarsize.y - 1 * LL_FUEL_CONSUMTION;
                fuelbar.setSize(fuelbarsize);

                fuelbarpoz.y = fuelbarpoz.y + 1 * LL_FUEL_CONSUMTION;
                fuelbar.setPosition(fuelbarpoz);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && fuelbarsize.y > 0) {
                velocity_y -= 4 * LONG_LANDER_THRUST * cos(angle);
                velocity_x += 4 * LONG_LANDER_THRUST * sin(angle);
                mainengine = true;
                landed = false;
                fuelbarsize.y = fuelbarsize.y - 4 * LL_FUEL_CONSUMTION;
                fuelbar.setSize(fuelbarsize);

                fuelbarpoz.y = fuelbarpoz.y + 4 * LL_FUEL_CONSUMTION;
                fuelbar.setPosition(fuelbarpoz);
            }
        }
        if(!dead)
            engine_on = true;
        if (mainengine)
        {
            if (!left_engine && !right_engine)
                body.setTexture(&texture[1]);
            else if (left_engine && !right_engine)
                body.setTexture(&texture[4]);
            else if (!left_engine && right_engine)
                body.setTexture(&texture[5]);
            else
                body.setTexture(&texture[7]);
        }
        else
        {
            if (!left_engine && !right_engine) {
                body.setTexture(&texture[0]);
                engine_on = false;
            }
            else if (left_engine && !right_engine)
                body.setTexture(&texture[2]);
            else if (!left_engine && right_engine)
                body.setTexture(&texture[3]);
            else {
                body.setTexture(&texture[6]);
            }
        }
    }
    else {
        body.setTexture(&texture[0]);
    }

    if (!landed) {
        velocity_y += GRAVITY;
        movement.x = velocity_x;
        movement.y += velocity_y;
        body.move(movement);
    }
    if (LandingDetect(lines) && !dead) {
        dead = !GoodLanding(angle, velocity_y, landed);

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
}

void LongLander::Draw(sf::RenderWindow& window) {
    window.draw(body);
    window.draw(fuelbar);
}

bool LongLander::CollisionDetect(sf::VertexArray& lines)
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
            if ((int)position.x == j-30 && (int)position.y + LONG_LANDER_BODY_SIZE_Y / 2 >= lines[i].position.y + y_addition)
            {
                body.setPosition(position.x, lines[i].position.y + y_addition - LONG_LANDER_BODY_SIZE_Y / 2);
                return true;
            }
            if ((int)position.x == j+30 && (int)position.y + LONG_LANDER_BODY_SIZE_Y / 2 >= lines[i].position.y + y_addition)
            {
                body.setPosition(position.x, lines[i].position.y + y_addition - LONG_LANDER_BODY_SIZE_Y / 2);
                return true;
            }
            y_addition += m;
        }
    }
    return false;
}

bool LongLander::LandingDetect(sf::VertexArray& lines)
{
    sf::Vector2f position(0.0f, 0.0f);
    position = body.getPosition();

    for (int i = lines[LANDINGSITE1].position.x; i < lines[LANDINGSITE1 + 1].position.x; ++i)
    {

        if ((int)position.x == i-30 && (int)position.y + LONG_LANDER_BODY_SIZE_Y/2 >= lines[LANDINGSITE1].position.y)
        {
            body.setPosition(position.x, lines[LANDINGSITE1].position.y - LONG_LANDER_BODY_SIZE_Y / 2);
            return true;
        }
        if ((int)position.x == i+30 && (int)position.y + LONG_LANDER_BODY_SIZE_Y / 2 >= lines[LANDINGSITE1].position.y)
        {
            body.setPosition(position.x, lines[LANDINGSITE1].position.y - LONG_LANDER_BODY_SIZE_Y / 2);
            return true;
        }
    }
    for (int i = lines[LANDINGSITE2].position.x; i < lines[LANDINGSITE2 + 1].position.x; ++i)
    {
        if ((int)position.x == i - 30 && (int)position.y + LONG_LANDER_BODY_SIZE_Y / 2 >= lines[LANDINGSITE2].position.y)
        {
            body.setPosition(position.x, lines[LANDINGSITE2].position.y - LONG_LANDER_BODY_SIZE_Y / 2);
            return true;
        }
        if ((int)position.x == i + 30 && (int)position.y + LONG_LANDER_BODY_SIZE_Y / 2 >= lines[LANDINGSITE2].position.y)
        {
            body.setPosition(position.x, lines[LANDINGSITE2].position.y - LONG_LANDER_BODY_SIZE_Y / 2);
            return true;
        }
    }
    return false;
}

bool LongLander::GoodLanding(float angle, float velocity_y, bool& landed)
{
    angle /= (M_PI / 180);
    if ((angle < GOOD_ANGLE || angle > 360 - GOOD_ANGLE) && velocity_y < 0.5) {
        body.setRotation(0);
        landed = true;
        return true;
    }
    return false;
}

bool LongLander::OffWindow()
{
    sf::Vector2f position(0.0f, 0.0f);
    position = body.getPosition();
    if (position.x<0 || position.x>SCREEN_SIZE_X || position.y<0 || position.y>SCREEN_SIZE_Y) {
        return true;
    }
    return false;
}