#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <string>
#include <cstdlib>
#include <time.h>

#define BODY_HALF_SIZE			32.0
#define LONG_LANDER_BODY_SIZE_X	97.0			//long lander
#define LONG_LANDER_BODY_SIZE_Y 65.0			//long lander
#define SCREEN_SIZE_X			1200
#define SCREEN_SIZE_Y			800
#define GRAVITY					0.01
#define THRUST					(3*GRAVITY)
#define LONG_LANDER_THRUST		(0.21*GRAVITY)	//long lander
#define LL_ROTATION_SPEED		0.3				//long lander
#define ROTATION_SPEED			1.0
#define LANDER_PICS				9
#define LONG_LANDER_PICS		8				//long lander
#define LANDING_SITE_PICS		1
#define GOOD_ANGLE				12
#define START_X					200
#define START_Y					700
#define LINECOUNT				16
#define LANDINGSITE1			1
#define LANDINGSITE2			12
#define MENUMAXCOUNT			10
#define MAINMENUCOUNT			2
#define PLAYMENUCOUNT			3
#define PAUSEMENUCOUNT			2
#define MENU_FONTSIZE			96

#define FUELBAR_SIZE_X			20
#define FUELBAR_SIZE_Y			200
#define FUEL_CONSUMTION			0.25
#define LL_FUEL_CONSUMTION		0.015			//long lander	