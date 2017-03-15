//
//  Globals.h
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#ifndef KittehAdventure_Globals_h
#define KittehAdventure_Globals_h

#include "cocos2d.h"


#ifndef DEBUG 
//#define DEBUG 1
#endif

USING_NS_CC;

//#define ANDROID

enum { LOAD, INTRO,PLAYMODE, END_OF_LEVEL, POWER_UP,PAUSE,DIED,GAMEOVER,CLEAN_UP,SHOW_STATS,ERROR,RESET,DONE,WAIT };

enum { TITLE_FADEIN, TITLE_DONE };

enum { COIN, POWERUP,LIFE };

enum { GAMEOVER_FADEIN, GAMEOVER_FADE_DONE };

//Specials
enum { BIG_KITTEH, MEOW_KITTEH,LONG_KITTEH,GRUMPY_KITTEH,CEILING_KITTEH };

static const char* tilePNG = "Tile.png";
static const char* jungleTitle1 = "JungleTitleGround1.png";

static int level=0;

static int totalLevels=5;

static int totalCoins=0;
static int coins=0;
static int totalKittehSave=0;

namespace Globals
{
	static int Coins;
}




#endif
