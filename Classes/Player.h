//
//  Player.h
//  KittehAdventure
//
//  Created by code on 2014/11/10.
//
//

#ifndef __KittehAdventure__Player__
#define __KittehAdventure__Player__

#include <stdio.h>
#include "cocos2d.h"
#include "LiveObject.h"
#include "../CocosDenshion/include/SimpleAudioEngine.h"


USING_NS_CC;

enum state { IDLE,RUNNING };

class Player:  public LiveObject
{
    public:
        Player();
        ~Player();
    
        int coins;

        bool init();
        virtual void Update(float dt);
    
    
        CCArray* kittens;
        Object* must;
        //Special
        float startTime;
        float totalTime;
        bool isFinished;
        bool isDone;
        bool special;
        int specialID;
        void DoSpecial(int specialID);
        void SpecialRunning(float dt);
        Object* box;
        CCArray* lasersParts;
    
    
};

#endif /* defined(__KittehAdventure__Player__) */
