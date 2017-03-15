//
//  Level.h
//  KittehAdventure
//
//  Created by code on 2014/11/02.
//
//

#ifndef __KittehAdventure__Level__
#define __KittehAdventure__Level__

#include <stdio.h>
#include "cocos2d.h"
#include "Globals.h"
#include "Player.h"
#include "Enemy.h"
#include "AnimeText.h"
#include "Item.h"
#include "LoadLevel.h"
#include "Title.h"
#include "../CocosDenshion/include/SimpleAudioEngine.h"
#include "Ending.h"
#include "AppDelegate.h"
//#include "../external/Box2d/Box2D.h"

USING_NS_CC;


class Level : public cocos2d::CCLayer
{
    public:


    
        Player* kitteh;
        CCLabelTTF* coinDisplay;
        CCArray* tiles;
        CCArray* enimes;
        CCArray* items;
        Enemy* shroom;
        AnimeText* theText;
        AnimeText* levelTitle;
        AnimeText* GameoverText;
        Object* coinIcon;
        LoadLevel* loadingScreenLayer;
        CCSequence* walkSec;
        CCArray* backgrounds;
        CCString* levelBackgroundMusic;
        Object* display;
    
    
        int newState;
        int state;
        bool gravity;
        float titleFade;
        float pauseAmount;
        float pauseCount;
        int titleState;
        float tilePadding;
        float levelEnd;
        float kittehSpeed;
        int gameOverStatus;
        bool isLoading;
        float musicVolume;
    
        bool music;

        virtual bool init();
        static cocos2d::CCScene* scene();
        void Update(float dt);
        void ccTouchesEnded(CCSet* touches, CCEvent* event);
        void LoadingScreen(float dt);
        void PauseGame();
        void CleanUp();
        Object* box;

        CREATE_FUNC(Level);

};


#endif /* defined(__KittehAdventure__Level__) */
